import java.io.*;
import java.util.*;
import java.lang.Math;

//This program calculates the shortest distance that two salesmen would have to travel
//to reach every city in the city2.dat file.

public class Salesmen {

    public static void main (String[] args){
        int num = 0;
        int xOrY = 0;
        int currCity = 0;
        int coordinates[][];
        
        try{
            Scanner fileScan = new Scanner (new File("city2.dat"));
                
            num = fileScan.nextInt();
            
            coordinates = new int[2][num];

            while(fileScan.hasNext()){
                num = fileScan.nextInt();
                coordinates[xOrY][currCity] = num;
                if(xOrY == 1){
                    currCity++;
                    xOrY = 0;
                }
                else{
                    xOrY = 1;
                }
            }
            
            fileScan.close();
        }
        catch( Exception e){
            coordinates = new int[2][999];
            System.err.println("Error: " + e.getMessage());
        }


        //Distance formula on everything
        int distances [][] = new int[currCity][currCity];
        for(int i = 0; i < currCity; i++){
            for(int j = 0; j < currCity; j++){
                if(i != j){
                    int x1 = coordinates[0][i];
                    int y1 = coordinates[1][i];
                    int x2 = coordinates[0][j];
                    int y2 = coordinates[1][j];
                    distances[i][j] = (int) (Math.sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
                }
                else{
                    distances[i][j] = 99999;
                }
            }
        }

        //Salesman 1 hometown: Sacramento California
        //Salesman 2 hometown: Raleigh North Carolina

        int s1 = 3;
        int s2 = 30;
        boolean visited[] = new boolean[currCity];
        for(int i = 0; i < currCity; i++){
            visited[i] = false;
        }

        visited[s1] = true;
        visited[s2] = true;
        boolean allDone = false;
        
        int s1Travel = 0;
        int s2Travel = 0;
        int s1Path[] = new int[currCity/2 + 1];
        int s2Path[] = new int[currCity/2 + 1];

        s1Path[0] = s1;
        s1Path[currCity/2] = s1;
        s2Path[0] = s2;
        s2Path[currCity/2] = s2;

        int stopNum = 1;

        int s1BestCity = s1;
        int s2BestCity = s2;

        //visit places
        
        while(allDone == false){
           
            int s1BestDist = 99999;

            while( visited[s1BestCity] ){
                for(int i = 0; i < currCity; i++){
                     if(distances[s1][i] < s1BestDist){
                         if(!visited[i]){
                             s1BestDist = distances[s1][i];
                             s1BestCity = i;
                             s1Path[stopNum] = s1BestCity;
                         }
                     }
                }
            }
            visited[s1BestCity] = true;
            s1 = s1BestCity;
            s1Travel += s1BestDist;
            
            int s2BestDist = 99999;
            while( visited[s2BestCity]){
                for(int i = 0; i < currCity; i++){
                   if(distances[s2][i] < s2BestDist){
                      if(!visited[i]){
                         s2BestDist = distances[s2][i];
                         s2BestCity = i;
                         s2Path[stopNum] = s2BestCity;
                      }
                   }
                }
            }
            visited[s2BestCity] = true;
            s2 = s2BestCity;
            s2Travel += s2BestDist;
 
            allDone = true;
 
            for(int i = 0; i < currCity; i++){
                if( !visited[i] ){
                    allDone = false;
                }
            }
 
            stopNum++;
         }
 
         s1Travel += distances[s1BestCity][s1Path[0]];
         s2Travel += distances[s2BestCity][s2Path[0]];
 
         System.out.println("Salesman 1's Route: ");
         for(int i = 0; i < currCity/2 + 1; i++){
             System.out.print(s1Path[i] + " ");
         }
 
         System.out.println("\nDistance Travelled: ");
         System.out.println(s1Travel);
 
         System.out.println("Salesman 2's Route: ");
         for(int i = 0; i < currCity/2 + 1; i++){
             System.out.print(s2Path[i] + " ");
         }
 
         System.out.println("\nDistance Travelled: ");
         System.out.println(s2Travel);

         System.out.println("\nTotal Distance Travelled: ");
         System.out.println((s1Travel + s2Travel));
     }
}

