"""djangoPW URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.10/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url, include
from django.contrib import admin
from . import views

urlpatterns = [
    url(r'^admin/', admin.site.urls),
    url(r'^empresa/',include('empresa.urls',namespace='empresa')),
    url(r'^cursos/', include('cursos.urls', namespace='cursos')),
    url(r'^practicas/',include('practicas.urls', namespace='practicas')),
    url(r'^buscar_zona/$',views.buscar_zona, name ='buscar'),
    url(r'^buscar_zona/(?P<zona>.*)$',views.listar_zona, name='listar_zona'),
    url(r'^buscar_empresa/$',views.buscar_empresa, name='buscar_empresa'),
    url(r'^buscar_tematica/$',views.buscar_tematica, name='buscar_tematica'),
    url(r'^$',views.index, name='index'),
]
