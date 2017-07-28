from django.conf.urls import url
from . import views
from django.conf import settings

urlpatterns = [ 
	url(r'^nuevo_curso$',views.Nuevo_curso, name="nuevo_curso"),
	url(r'^lista_cursos$',views.Lista_cursos, name="lista_cursos"),
	url(r'^detalle/(?P<curso_nombre>.*)$',views.Detalle_curso, name="detalle_curso"),
	url(r'^modificar/(?P<curso_nombre>.*)$',views.Modificar_curso, name="modificar_curso"),
	url(r'^mis_cursos/$',views.Mis_cursos, name="mis_cursos"),
	url(r'^eliminar_curso/(?P<pk>[0-9]+)/$', views.Eliminar_curso, name="eliminar_curso"),
	]