from django.shortcuts import render, redirect, get_object_or_404
from django.http import HttpResponse
from empresa.models import Empresa
from .models import Curso
from django.contrib.auth.decorators import login_required
from .form import NuevoCursoForm, ModificarCursoForm

# Create your views here.

@login_required(login_url="/empresa/login")
def Nuevo_curso(request):
	if request.method== 'POST':
		form = NuevoCursoForm(request.POST)
		if form.is_valid():
			empresa_aux=get_object_or_404(Empresa, username=request.user.username)
			nuevo_curso= Curso()
			nuevo_curso.nombre=request.POST['nombre']
			nuevo_curso.descripcion=request.POST['descripcion']
			nuevo_curso.horas = request.POST['horas']
			nuevo_curso.inicio = request.POST['inicio']
			nuevo_curso.final= request.POST['final']
			nuevo_curso.precio = request.POST['precio']
			nuevo_curso.zona =request.POST['zona']
			nuevo_curso.target = request.POST['target']

			nuevo_curso.empresa=empresa_aux

			nuevo_curso.save()

			return redirect("/cursos/mis_cursos")
	else:
		form = NuevoCursoForm()
	context= {'form':form}
	return render(request,'cursos/NuevoCurso.html', context)


def Lista_cursos(request):
	list_cursos = Curso.objects.all().order_by('inicio')
	if len(list_cursos) == 0:
		msg="No hay cursos en estos momentos"
	else:
		msg="Hay cursos disponibles ahora mismo"
	context={'msg':msg, 'list_cursos':list_cursos }
	return render(request,'cursos/Lista_cursos.html',context)

def Detalle_curso(request,curso_nombre):
	curso = get_object_or_404(Curso, nombre=curso_nombre)
	return render(request,"cursos/Detalle_curso.html",{'curso':curso})

@login_required(login_url="/empresa/login")
def Modificar_curso(request, curso_nombre):
	curso = get_object_or_404(Curso, nombre=curso_nombre)
	if curso.empresa.username == request.user.get_username():
		if request.method == 'POST':
			form = ModificarCursoForm(request.POST, instance=curso)
			if form.is_valid():
				form.save()
				return redirect("/cursos/mis_cursos")
		else:
			form = ModificarCursoForm(instance=curso)
		context={'form': form, 'curso':curso}
		return render(request, "cursos/Modificar_curso.html",context)

	else:
		return HttpResponse("No es tu curso, no se modifica")

@login_required(login_url="/empresa/login")
def Mis_cursos(request):
	empresa_aux=Empresa.objects.get(username=request.user.get_username())
	list_cursos = Curso.objects.filter(empresa=empresa_aux).order_by('inicio')
	if len(list_cursos) == 0:
		msg="No ofreces cursos en estos momentos"
	else:
		msg="Ofreces estos cursos ahora mismo"
	context={'msg':msg, 'list_cursos':list_cursos }
	return render(request,'cursos/Lista_cursos_empresa.html',context)


@login_required(login_url="/empresa/login")
def Eliminar_curso(request, pk):
	curso=get_object_or_404(Curso,pk=pk)
	if curso.empresa.username == request.user.get_username(): 
		if request.method == 'POST':
			curso.delete()
			return redirect("/cursos/mis_cursos")
		else:
			return render(request,'cursos/Eliminar_curso.html',{'curso':curso})
	else:
		return HttpResponse("Este no es tu curso")