/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica1;
import practica1.factorial.factorial;

import java.util.Scanner;

/**
 *
 * @author hidesagred
 */
public class Practica1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner sc=new Scanner(System.in);
        int opt=1;
        do{
            do{

            System.out.println("\nEscoja una opción:");
            System.out.println("\t1.Calcular el factorial:");
            System.out.println("\t2.Clase profesor:");
            System.out.println("\t0.Salir del programa");
            opt=sc.nextInt();
        
        
                switch (opt) {
                    case 0:
                        System.out.println("Saliendo del programa....");
                        break;
                    case 1:
                        System.out.println("Introduzca un valor para calcular le factorial. Si es menor que 0 no se calcula:");
                        int factor= sc.nextInt();
                        if(factor>=0){
                            factorial fac= new factorial();
                            double res = fac.CalculaFactorial(factor);

                            System.out.println("El resultado del factorial de " + factor +" es " + res);
                        }else{
                            System.out.println("No se puede calcular el facotorial de un numero negativo");
                        }
                        break;
                    case 2:
                        System.out.println("Se muestra la clase profesor:");
                        profesor p=new profesor("Miguel", "Ruiz del Valle", 34, "UCO", 19832135);
                        
                        p.mostrarDatos();
                      
                        p.modificarDatos();
                        
                        System.out.println("Se muestran los datos del nuevo profesor: ");
                        p.mostrarDatos();
                        
                        break;
                    default:
                        System.out.println("La opción " + opt + " no es valida. ");
                }

            
            }while(opt<0 && opt>2);
        }while(opt!=0);
    }
    
}
