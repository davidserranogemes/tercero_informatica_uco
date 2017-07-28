from cursos.models import Curso
from django import forms
from django.forms import ModelForm
from django.forms.extras.widgets import SelectDateWidget


class NuevoCursoForm(ModelForm):
	class Meta:
		model = Curso
		exclude=['empresa']
class ModificarCursoForm(ModelForm):
	class Meta:
		model = Curso
		exclude=['empresa']