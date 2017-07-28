from django.shortcuts import render, redirect
from .form import BuscarZonaForm, BuscarEmpresaForm, BuscarTematicaForm
from django.http import HttpResponse
from cursos.models import Curso
from practicas.models import Practica
from empresa.models import Empresa

def index(request):
	return render(request,'djangoPW/index.html')


def buscar_zona(request):
	if request.method == 'POST':
		form = BuscarZonaForm(request.POST)
		if form.is_valid():
			zona=request.POST['zona']
			url='/buscar_zona/'+str(zona)
			return redirect(url)
	else:
		form = BuscarZonaForm()
	context={'form':form}
	return render(request,'djangoPW/Buscar_zona.html',context)

def listar_zona(request, zona):
	lista_curso=Curso.objects.filter(zona__icontains=zona)
	lista_practica=Practica.objects.filter(zona__icontains=zona)
	context={'lista_curso':lista_curso, 'lista_practica':lista_practica,'zona':zona}
	return render(request,'djangoPW/Lista_zona.html',context)

def buscar_empresa(request):
	if request.method == 'POST':
		form=BuscarEmpresaForm(request.POST)
		if form.is_valid():
			empresa=request.POST['empresa']
			lista_empresas=Empresa.objects.filter(nombre__icontains=empresa)
			return render(request,'djangoPW/Listar_empresas.html',{'empresa':empresa,'lista_empresas':lista_empresas})
	else:
		form=BuscarEmpresaForm()
	context={'form':form}
	return render(request,'djangoPW/Buscar_empresa.html',context)

def buscar_tematica(request):
	if request.method == 'POST':
		form=BuscarTematicaForm(request.POST)
		if form.is_valid():
			tema=request.POST['tema']
			lista_cursos=Curso.objects.filter(descripcion__icontains=tema)
			lista_practicas=Practica.objects.filter(descripcion__icontains=tema)
			context={'tema':tema,'lista_cursos':lista_cursos,'lista_practicas':lista_practicas}
			return render(request,'djangoPW/Listar_tematica.html',context)
	else:
		form=BuscarTematicaForm()
	context={'form':form}
	return render(request,'djangoPW/Buscar_tematica.html',context)