/*
MIT License

Copyright (c) 2020 Onat Özbay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define Population   100

float Random_No() {
   return ((float)(rand()%100))/(100);
}

int Ruffle_Char(int r) {
   return (rand()%r);
}

char Reference_Input[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890.:,;!?";
char Reference_Output[]="The quick brown fox jumps over the lazy dog.";

struct Individuals {
   char *Chromosome;
   int Fitness;
};

char *Make() {
   int Length=strlen(Reference_Output);
   char *Steam=malloc(Length+1);

   for (int i=0; i<Length; i++) {
      Steam[i]=Reference_Input[Ruffle_Char(strlen(Reference_Input))];
   }

   Steam[Length] = '\0';

   return Steam;
}

char *Mate(struct Individuals Parent_1, struct Individuals Parent_2) {
   int Length=strlen(Reference_Output);
   char *Child=malloc(Length+1);

   for(int i=0; i<Length; i++) {
      float r=Random_No();

      if(r<0.48) {
         Child[i]=Parent_1.Chromosome[i];
      }

      else if(r<0.96) {
         Child[i]=Parent_2.Chromosome[i];
      }

      else {
         Child[i]=Reference_Input[Ruffle_Char(strlen(Reference_Input))];
      }
   }

   Child[Length]='\0';

   return Child;
}

int Measure(struct Individuals Person) {
   int Fitness=0, Length=strlen(Reference_Output);

   for(int i=0; i<Length; i++) {
      if(Person.Chromosome[i]==Reference_Output[i]) {
         Fitness++;
      }
   }

   return Fitness;
}

void *Sort(struct Individuals Person[]) {
   struct Individuals Rubbish;

   for(int i=0; i<Population; i++) {
      for (int j=0; j<Population-1; j++) {
         if (Person[j].Fitness<Person[j+1].Fitness) {
            Rubbish.Chromosome=Person[j].Chromosome;
            Person[j].Chromosome=Person[j+1].Chromosome;
            Person[j+1].Chromosome=Rubbish.Chromosome;

            Rubbish.Fitness=Person[j].Fitness;
            Person[j].Fitness=Person[j+1].Fitness;
            Person[j+1].Fitness=Rubbish.Fitness;
         }
      }
   }

   return Person;
}

int main() {
   srand(time(NULL));
   struct Individuals Generation[Population], New_Generation[Population];

   int Watchdog=0, Percent=((10*Population)/100);

   for(int i=0; i<Population; i++) {
      Generation[i].Chromosome=Make();
      Generation[i].Fitness=Measure(Generation[i]);
   }

   Sort(Generation);

   Watchdog++;

   printf("%s\tFitness: [%ld%%]\tGeneration: [%d]\n", Generation[0].Chromosome, ((Generation[0].Fitness*100)/strlen(Reference_Output)), Watchdog);

   do {
      for(int i=0; i<Percent; i++) {
         New_Generation[i]=Generation[i];
      }

      for(int i=Percent; i<Population; i++) {
         int R=rand()%(Population/2);
         struct Individuals Person_1=Generation[R];
         R=rand()%(Population/2);
         struct Individuals Person_2=Generation[R];

         New_Generation[i].Chromosome=Mate(Person_1, Person_2);
         New_Generation[i].Fitness=Measure(New_Generation[i]);
      }

      Sort(New_Generation);

      for(int i=0; i<Population; i++) {
         Generation[i]=New_Generation[i];
      }

      Watchdog++;

      printf("\n%s\tFitness: [%ld%%]\tGeneration: [%d]\n", Generation[0].Chromosome, ((Generation[0].Fitness*100)/strlen(Reference_Output)), Watchdog);

   } while(Generation[0].Fitness!=strlen(Reference_Output));
}
