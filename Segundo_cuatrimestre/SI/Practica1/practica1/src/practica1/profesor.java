/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica1;

import java.util.Scanner;

/**
 *
 * @author hidesagred
 */
public class profesor extends persona {
    private String _universidad;
    private int _id_profesor;
    
    public profesor(String nombre, String apellidos, int edad, String universidad, int id){
        super(nombre, apellidos, edad);
        _universidad=universidad;
        _id_profesor=id;
    }
    
    public void setUniversidad(String universidad){
        _universidad=universidad;
    }
    public void setId(int id){
        _id_profesor=id;
    }
    public String getUniversidad(){
        return _universidad;
    }
    public int getId(){
        return _id_profesor;
    }
    
    public void mostrarDatos(){
        System.out.println("El profesor " + getNombre() + " " + getApellidos() +
                " con edad " + getEdad() + " trabaja en la universidad " +
                getUniversidad()+ " y tiene un id de profesor " + getId());
    }
    
    public void modificarDatos(){
          String auxString;
          int auxInt;
          Scanner sc= new Scanner(System.in);
                    
          System.out.println("Modifique los datos ahora. Introduzca el nombre:");
          auxString=sc.nextLine();
          setNombre(auxString);
                        
          System.out.println("Introduzca los apellidos:");
          auxString=sc.nextLine();
          setApellidos(auxString);
                        
          System.out.println("Introduzca la edad:");
          auxInt=sc.nextInt();
          setEdad(auxInt);
                        
          sc.nextLine();//Igual que antes limpia el buffer
                        
          System.out.println("Introduzca la universidad:");
          auxString=sc.nextLine();
          setUniversidad(auxString);
                        
          System.out.println("Introduzca la id del profesor:");
          auxInt=sc.nextInt();
          setId(auxInt);
    }
}
