/* @Author
 * Student Name: Bulent Koray OZ
 * Student ID :	 150130281
 * Date: 23/11/2016
 */

#ifndef LIST_H
#define	LIST_H

#include <iostream>
#include "node_structs.h"

typedef struct list {
	FILE* songlist;
	STATUS status = NOTSTARTED;
	char* filename = "songbook.txt";
	int playlist_count;
	playlist* head;
	void createList(char* plName); // Default olan 3 playlist i ve daha sonradan eklenen playlistleri baslatir.
	void addSong(char* Lname, char* Sname); // Playlistlere SORTED playlist den sarki ekler.
	void playL(char* Lname, char* Sname); 
	void navigate(song_node* node); // Play komutunda sarki degisimini saglar.
	bool removeSong(char* select_list, char* select_song); 
	bool deleteList(char* ); 
	void writeToFile(); 
	void makeEmpty(); // Butun verileri deallocate yapar.
	song_node* full_chrono(); // Baslangicta CHRONOLOGICAL playlist in icini doldurur.
	song_node* full_sorted(); // Baslangicta SORTED playlist in icini doldurur.
	song_node* full_random(); // Baslangicta RANDOM playlist in icini doldurur.
	void full_user(char select); // Sonradan olusturulan user-defined playlistlerin iclerini doldurur.
	void Customlist(); // Baslangicta dosyada CHRONOLOGICAL playlist in disinda kayitli olan playlist i olusturur ve dosyadan okur.
	bool isfinished(); // Baslangicta dosyada CHRONOLOGICAL playlist den baska playlist olup olmadigini kontrol eder.
	bool print(char* selection); // Secilen playlist in icinde kayitli olan sarkilari yazdirir.

}type;

#endif // !LIST_H
