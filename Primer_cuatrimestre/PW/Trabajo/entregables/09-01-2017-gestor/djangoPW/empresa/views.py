from __future__ import unicode_literals
from django.http import HttpResponse
from django.shortcuts import render, redirect, get_object_or_404
from .models import Empresa
from cursos.models import Curso
from practicas.models import Practica
from django.contrib.auth.models import User
from django.contrib.auth import authenticate, login, logout
from django.core.urlresolvers import reverse_lazy
from empresa.form import EmpresaResgisterForm, EmpresaLoginForm, ModificarEmpresaForm,CambiarContraseniaForm
from django.views.generic.detail import DetailView
from django.contrib.auth.decorators import login_required


# Create your views here.

def Registro(request):
	if request.user.is_authenticated():
		return HttpResponse("Ya estas registrado")
	else:
		if request.method == 'POST':
			form = EmpresaResgisterForm(request.POST,request.FILES)
			if form.is_valid():
				form.save()
				return redirect("/empresa/agregado")
		else:
			form = EmpresaResgisterForm()
		context = {'form':form}
		return render(request,'empresa/RegistroEmpresa.html',context) 

def Agregado(request):
	return render(request, 'empresa/Agregado.html')

def Login(request):
	if request.user.is_authenticated():
		return redirect("/empresa/already_loged")
	else:
		if request.method == 'POST':
			username = request.POST['username']
			password = request.POST['password']
			user = authenticate(username=username, password=password)
			if user is not None:
				login(request, user)
				return redirect("/empresa/mi_empresa")
			else:
				return redirect("/empresa/login")
		else:
			form = EmpresaLoginForm()
		context = {'form':form}
		return render(request,'empresa/LoginEmpresa.html',context)

def Logout(request):
	if request.user.is_authenticated():
		logout(request)
		return render(request, "empresa/Logout.html")
	else:
		return redirect("/empresa/not_loged")

def Already_loged(request):
	return render(request,"empresa/Already_loged.html")
def Not_loged(request):
	return render(request,"empresa/Not_loged.html")

@login_required()
def Mi_empresa(request):
	empresa = get_object_or_404(Empresa, username=request.user.get_username())
	mis_cursos = Curso.objects.filter(empresa=empresa)
	mis_practicas = Practica.objects.filter(empresa=empresa)
	context={"empresa":empresa,"mis_cursos":mis_cursos, "mis_practicas":mis_practicas}
	return render(request,"empresa/Mi_empresa.html",context)

@login_required()
def Modificar_mi_empresa(request):
	empresa=get_object_or_404(Empresa, username=request.user.get_username())
	if request.method == 'POST':
		form = ModificarEmpresaForm(request.POST, instance=empresa)
		if form.is_valid():
			form.save()
			return redirect("/empresa/mi_empresa")
	else:
		form= ModificarEmpresaForm(instance=empresa)
	context={'form':form, 'empresa':empresa}
	return render(request, 'empresa/Modificar_empresa_form.html',context)

@login_required()
def Cambiar_contrasenia(request):
	empresa=get_object_or_404(Empresa, username=request.user.get_username())
	msg = "Las dos contrasenias deben ser iguales"
	if request.method == 'POST':
		password_actual= request.POST['password_actual']
		password = request.POST['password']
		password_check = request.POST['password_check']

		if empresa.check_password(password_actual):
			if password == password_check:
				empresa.set_password(password)
				empresa.save()
				# Cuando cambiamos la contrasenia de la empresa actual se deslogea automaticamente por lo que le hacemos un login automatico
				user = authenticate(username=empresa.username, password=password)
				if user is not None:
					login(request, user)
					return redirect("/empresa/mi_empresa")
				else:
					return redirect("/empresa/login")
				
			else:
				msg = "Las contrasenias no coinciden"
				form = CambiarContraseniaForm()
		else:
			msg = "Esa no es su contrasenia actual"
			form = CambiarContraseniaForm()
	else:
		form = CambiarContraseniaForm()
	context={'msg':msg,'form':form}
	return render(request, "empresa/Cambiar_contrasenia_form.html",context)



def Detalle_empresa(request,pk):
	empresa=get_object_or_404(Empresa, pk=pk)
	lista_cursos=Curso.objects.filter(empresa=empresa)
	lista_practicas=Practica.objects.filter(empresa=empresa)
	context={'empresa':empresa ,'lista_cursos':lista_cursos, 'lista_practicas':lista_practicas}
	return render(request,"empresa/Detalle_empresa_publico.html",context)