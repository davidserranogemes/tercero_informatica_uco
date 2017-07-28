from django import forms
from django.forms import ModelForm



class BuscarZonaForm(forms.Form):
	zona= forms.CharField()
class BuscarEmpresaForm(forms.Form):
	empresa=forms.CharField()
class BuscarTematicaForm(forms.Form):
	tema=forms.CharField()