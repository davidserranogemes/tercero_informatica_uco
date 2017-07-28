from django.shortcuts import render, redirect, get_object_or_404
from .models import Practica
from empresa.models import Empresa
from django.utils.decorators import method_decorator
from django.contrib.auth.decorators import login_required
from django.http import HttpResponse
from django.views.generic.detail import DetailView
from django.views.generic.list import ListView
from django.views.generic.edit import UpdateView


from .form import NuevaPracticaForm, ModificarPracticaForm
# Create your views here.

@login_required()
def Nueva_practica(request):
	if request.method == 'POST':
		form = NuevaPracticaForm(request.POST)
		if form.is_valid():
			empresa_aux=get_object_or_404(Empresa, username=request.user.username)
			nueva_practica = Practica()
			nueva_practica.nombre=request.POST['nombre']
			nueva_practica.descripcion=request.POST['descripcion']
			nueva_practica.empresa=empresa_aux
			nueva_practica.remuneracion=request.POST['remuneracion']
			nueva_practica.horas_semana = request.POST['horas_semana']
			nueva_practica.dias_trabajo = request.POST['dias_trabajo']
			nueva_practica.zona = request.POST['zona']
			nueva_practica.target = request.POST['target']
			nueva_practica.duracion = request.POST['duracion']
			nueva_practica.save()
			return redirect("/practicas/mis_practicas")
	else:
		form = NuevaPracticaForm()
	context= {'form':form}
	return render(request, 'practicas/NuevaPractica.html',context)
	
class Lista_practicas(ListView):
	model= Practica
	template_name='practicas/Lista_practicas.html'
	context_object_name = 'practicas_list'
	def get_queryset(self):
		return Practica.objects.all()



class Detalle_practica(DetailView):
	model = Practica
	template_name='practicas/Detalle_practica.html'

def Modificar_practica(request, pk):
	practica=get_object_or_404(Practica,pk=pk)
	if practica.empresa.username==request.user.get_username():
		if request.method == 'POST':
			form = ModificarPracticaForm(request.POST, instance=practica)
			if form.is_valid():
				form.save()
				return redirect("/practicas/mis_practicas")
		else:
			form = ModificarPracticaForm(instance=practica)
		context={'form':form, 'practica':practica}
		return render(request,"practicas/practica_update_form.html",context)
	else:
		return HttpResponse("No es tu practica, no se modifica")

class Mis_practicas(ListView):
	model= Practica
	template_name='practicas/Lista_practicas_empresa.html'
	context_object_name='practicas_list'
	def get_queryset(self):
		empresa=self.request.user
		return Practica.objects.filter(empresa=empresa)


@login_required()
def Eliminar_practica(request, pk):
	practica=get_object_or_404(Practica,pk=pk)
	if practica.empresa.username == request.user.get_username():
		if request.method == 'POST':
			practica.delete()
			return redirect("/practicas/mis_practicas")
		else:
			return render(request, "practicas/Eliminar_practica.html",{'practica':practica})
	else:
		return HttpResponse("Este no es tu practica")

