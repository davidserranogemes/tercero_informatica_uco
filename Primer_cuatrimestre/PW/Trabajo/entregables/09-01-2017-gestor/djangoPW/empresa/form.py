from empresa.models import Empresa
from django.contrib.auth.forms import UserCreationForm
from django import forms
from django.forms import ModelForm





#Usercreationform hashea la pass directamente

class EmpresaResgisterForm(UserCreationForm):
	class Meta:
		model = Empresa
		fields=('username','descripcion','telefono','email','nombre')

class EmpresaLoginForm(forms.Form):
	username = forms.CharField()
	password = forms.CharField(widget=forms.PasswordInput, label="Password")


class ModificarEmpresaForm(ModelForm):
	class Meta:
		model=Empresa
		fields=('nombre', 'descripcion','telefono','email')

class CambiarContraseniaForm(forms.Form):
	password_actual=forms.CharField(widget= forms.PasswordInput, label="Password actual")
	password=forms.CharField(widget=forms.PasswordInput, label="Nueva password")
	password_check=forms.CharField(widget= forms.PasswordInput, label="Repetir nueva password")
