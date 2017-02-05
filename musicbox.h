/* @Author
 * Student Name: Bulent Koray OZ
 * Student ID :	 150130281
 * Date: 23/11/2016
 */

#ifndef MUSICBOX_H
#define MUSICBOX_H

#include "node_structs.h"

void play(); 
void printList(); 
void createList(); 
void addSong(); 
void removeSong(); 
void deleteList(); 
void writeToFile(); 
void exit();	
void mainMenu_print(); 
void createMenu_print(); // createList komutu menusunu ekrana yazar.
void mainFunctions(char );
void doList(); // Var olan playlistleri listeler.
void editList(char* Lname, playlist** ptr); //printList() komutunda secim yapildiktan sonraki islemleri gercekler.
void printPlay(song song); // PLAY goruntusunu ekrana yazar.

#endif // !MUSICBOX_H
