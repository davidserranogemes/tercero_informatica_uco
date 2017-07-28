from practicas.models import Practica
from django import forms
from django.forms import ModelForm


class NuevaPracticaForm(ModelForm):
	class Meta:
		model= Practica
		exclude=['empresa']
class ModificarPracticaForm(ModelForm):
	class Meta:
		model=Practica
		exclude=['empresa']