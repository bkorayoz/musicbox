/* @Author
 * Student Name: Bulent Koray OZ
 * Student ID :	 150130281
 * Date: 23/11/2016
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include "musicbox.h"
#include "list.h"

using namespace std;

void list::createList(char* listname){

	if (status == NOTSTARTED) {

		playlist* traverse = new playlist;
		playlist* tail = new playlist;
		playlist* temp = new playlist;
		
		temp->head = full_chrono();
		temp->next = traverse;
		temp->prev = tail;
		temp->name = "CHRONOLOGICAL";
		temp->songnumber = 23;
		head = temp;
		playlist_count++;

		tail->head = full_random();
		tail->next = head;
		tail->prev = traverse;
		tail->name = "RANDOM";
		tail->songnumber = 23;
		playlist_count++;

		traverse->head = full_sorted();
		traverse->next = tail;
		traverse->prev = head;
		traverse->name = "SORTED";
		traverse->songnumber = 23;
		playlist_count++;

		if (isfinished()) {  // Baslangicta dosyada CHRONOLOGICAL playlist den baska playlist olup olmadigini kontrol eder.
			fclose(songlist);
		}
		else {
			Customlist(); // Varsa yeni liste olusturur ve dosyadan okur.
			fclose(songlist);
		}
		//fclose(songlist);
		status = STARTED;	
		return;
	}
	else if(status == STARTED){
	
		playlist* templist = new playlist;
		templist->head = NULL;
		strcpy(templist->name, listname);
		templist->songnumber = 0;
		templist->next = head;
		head->prev->next = templist;
		templist->prev = head->prev;
		head->prev = templist;	
		playlist_count++;
	}
}

void list::full_user(char select) {

	char data[LNAME_LENGTH];
	song_node* tempnode;
	song_node* headN = NULL;
	song_node* temp;

	switch (select) {
	case '1':
		tempnode = list::head->head;
		cout << "Enter the style you want to create list :" << endl;
		cin.getline(data, STYLE_LENGTH);

		do {
			if (strcmp(tempnode->data->style, data) == 0) {

				if (headN == NULL) { // Ilk sarki ekleniyor.
					temp = new song_node;
					temp->data = tempnode->data;
					temp->next = NULL;
					temp->prev = NULL;
					headN = temp;
				}
				else if (headN->next == NULL) { // Ikinci sarki ekleniyor.
					temp = new song_node;
					temp->data = tempnode->data;
					temp->next = headN;
					temp->prev = headN;
					headN->next = temp;
					headN->prev = temp;
				}
				else {
					temp = new song_node; // Sonraki sarkilar ekleniyor.
					temp->data = tempnode->data;
					headN->prev->next = temp;
					temp->prev = headN->prev;
					headN->prev = temp;
					temp->next = headN;
				}	
			}
			tempnode = tempnode->next;
		
		} while (tempnode != head->head);

		head->prev->head = headN; 
		break;

	case '2':
		tempnode = list::head->head;
		cout << "Enter the singer name you want to create list :" << endl;
		cin.getline(data, SINGER_LENGTH);

		do {
			if (strcmp(tempnode->data->singer, data) == 0) {

				if (headN == NULL) {
					temp = new song_node;
					temp->data = tempnode->data;
					temp->next = NULL;
					temp->prev = NULL;
					headN = temp;
				}
				else if (headN->next == NULL) {
					temp = new song_node;
					temp->data = tempnode->data;
					temp->next = headN;
					temp->prev = headN;
					headN->next = temp;
					headN->prev = temp;
				}
				else {
					temp = new song_node;
					temp->data = tempnode->data;
					headN->prev->next = temp;
					temp->prev = headN->prev;
					headN->prev = temp;
					temp->next = headN;

				}
			}
			tempnode = tempnode->next;

		} while (tempnode != head->head);

		head->prev->head = headN;
		break;

	case '3':
		playlist *templist, *templist2;
		templist = list::head;
		templist2 = list::head;
		char data2[LNAME_LENGTH];
		doList();
		cout << endl << "Enter the lists' names you want to merge to create a new list :" << endl;
		cin.getline(data, LNAME_LENGTH);
		cin.getline(data2, LNAME_LENGTH);

		while (strcmp(templist->name, data) != 0) { // merge edilecek listlerden 1. yi bulma
			templist = templist->next;
		}
		while (strcmp(templist2->name, data2) != 0) { // merge edilecek listlerden 2. yi bulma
			templist2 = templist->next;
		}
		tempnode = templist->head;
		do { // Birinci list i kopyaliyor.
				if (headN == NULL) {
					temp = new song_node;
					temp->data = tempnode->data;
					temp->next = NULL;
					temp->prev = NULL;
					headN = temp;
				}
				else if (headN->next == NULL) {
					temp = new song_node;
					temp->data = tempnode->data;
					temp->next = headN;
					temp->prev = headN;
					headN->next = temp;
					headN->prev = temp;
				}
				else {
					temp = new song_node;
					temp->data = tempnode->data;
					headN->prev->next = temp;
					temp->prev = headN->prev;
					headN->prev = temp;
					temp->next = headN;
				}
			
			tempnode = tempnode->next;

		} while (tempnode != templist->head);

		tempnode = templist2->head;
		do { // 2. list i 1. nin altina kopyaliyor.
			temp = new song_node;
			temp->data = tempnode->data;
			headN->prev->next = temp;
			temp->prev = headN->prev;
			headN->prev = temp;
			temp->next = headN;

			tempnode = tempnode->next;
		} while (tempnode != templist2->head);
		head->prev->head = headN; 
		break;

	case '4':
		cout << "New list is created. You can add songs one by one." << endl;
		break;

	default:
		cout << endl << "Wrong choice! Try again!" << endl;
		break;
	}


}

song_node* list::full_sorted() {

	song_node* head = NULL;
	song_node* temp, *traverse, *tail;
	song* record;
	

	if (songlist = fopen("songbook.txt", "r+")) {
		if (songlist == NULL) {
			cerr << "File could not be openned!" << endl;
			exit(0);
		}

		for (int i = 0; !(feof(songlist)) && i < 23; i++) {

			record = new song;

			fscanf(songlist, "\n%[^\t]\t%[^\t]\t%d\t%s", record->name, record->singer, &record->year, record->style);
			traverse = head;
			if (head == NULL) {

				temp = new song_node;
				temp->data = record;
				temp->next = NULL;
				temp->prev = NULL;
				head = temp;
				continue;
			}
			else if (head->next == NULL && strcmp(record->singer,head->data->singer) > 0) { // 2. veri head in altina

				temp = new song_node;
				temp->data = record;
				temp->next = head;
				temp->prev = head;
				head->next = temp;
				head->prev = temp;
				continue;
			}
			else if(head->next == NULL && strcmp(record->singer, head->data->singer) < 0) { // 2. veri head ile degisiyor.
			
				temp = new song_node;
				temp->data = record;
				temp->next = head;
				temp->prev = head;
				head->next = temp;
				head->prev = temp;
				head = temp;	
				continue;
			}
			if (strcmp(record->singer, head->data->singer) < 0) {
				
				temp = new song_node;
				temp->data = record;
				temp->next = head;
				temp->prev = head->prev;
				head->prev->next = temp;
				head->prev = temp;
				head = temp;
				continue;			
			}
			
			while (strcmp(record->singer, traverse->data->singer) > 0) {

				tail = traverse;
				traverse = traverse->next;
				if (traverse == head) { 
				
					temp = new song_node;
					temp->data = record;
					head->prev->next = temp;
					temp->prev = head->prev;
					head->prev = temp;
					temp->next = head;
					break;
				}
			}

				while (strcmp(record->singer, traverse->data->singer) == 0 && strcmp(record->name, traverse->data->name) > 0) {
				
					tail = traverse;
					traverse = traverse->next;
					if (traverse == head) { 

						temp = new song_node;
						temp->data = record;
						head->prev->next = temp;
						temp->prev = head->prev;
						head->prev = temp;
						temp->next = head;
						break;
					}
				}
				if (strcmp(record->singer, traverse->data->singer) < 0 || (strcmp(record->singer, traverse->data->singer) == 0 && strcmp(record->name, traverse->data->name) < 0)) {
					temp = new song_node; 
					temp->data = record;
					temp->next = traverse;
					temp->prev = tail;
					tail->next = temp;
					traverse->prev = temp;
				}
		}
	}
	
	return head;

}

song_node* list::full_chrono() {


	song_node* head = NULL;
	song_node* temp;
	song* record;

	if (songlist = fopen("songbook.txt", "r+")) {
		if (songlist == NULL) {
			cerr << "File could not be openned!" << endl;
			exit(0); 
		}

		for (int i = 0; !(feof(songlist)) && i < 23; i++) {

			record = new song;

			fscanf(songlist, "\n%[^\t]\t%[^\t]\t%d\t%s", record->name, record->singer, &record->year, record->style);

			if (head == NULL) {
			
				temp = new song_node;
				temp->data = record;
				temp->next = NULL;
				temp->prev = NULL;
				head = temp;
			}
			else if (head->next == NULL) {
				
				temp = new song_node;
				temp->data = record;
				temp->next = head;
				temp->prev = head;
				head->next = temp;
				head->prev = temp;			
			}
			else {

				temp = new song_node;
				temp->data = record;
				head->prev->next = temp;
				temp->prev = head->prev;
				head->prev = temp;
				temp->next = head;
				
			}
		}
	}
	
	return head;
}

song_node* list::full_random() {
	
	srand(time(NULL));
	int checkArray[23];
	for(int i = 0; i < 23; i++)
	checkArray[i] = 0;
	int randomnumber;
	song_node* head = NULL;
	song_node* temp;
	song* record;

	if (songlist = fopen("songbook.txt", "r+")) {
		if (songlist == NULL) {
			cerr << "File could not be openned!" << endl;
			exit(0); 
		}

		for (int i = 0; i < 23; i++) {

			record = new song;

			for (;;) {
				randomnumber = rand() % 23;
				if (checkArray[randomnumber] == 0) {
					checkArray[randomnumber] = 1;
					break;
				}
			}

			for (int i = 0; i < randomnumber ; i++) {
				fscanf(songlist, "\n%[^\t]\t%[^\t]\t%d\t%s", record->name, record->singer, &record->year, record->style);
			}

			fscanf(songlist, "\n%[^\t]\t%[^\t]\t%d\t%s", record->name, record->singer, &record->year, record->style);
			
			if (head == NULL) {

				temp = new song_node;
				temp->data = record;
				temp->next = NULL;
				temp->prev = NULL;
				head = temp;
			}
			else if (head->next == NULL) {

				temp = new song_node;
				temp->data = record;
				temp->next = head;
				temp->prev = head;
				head->next = temp;
				head->prev = temp;
			}
			else {

				temp = new song_node;
				temp->data = record;
				head->prev->next = temp;
				temp->prev = head->prev;
				head->prev = temp;
				temp->next = head;

			}
			rewind(songlist);
		}
	}
	
	return head;
}

void list::Customlist() {
	
	playlist* templist = new playlist;
	song_node* temp;
	song* record;
	templist->head = NULL;
	fscanf(songlist, "\n%s", templist->name);
	templist->songnumber = 0;
	templist->next = head;
	head->prev->next = templist;
	templist->prev = head->prev;
	head->prev = templist;
	playlist_count++;

	for (int i = 0; !(feof(songlist)); i++) {

		record = new song;

		fscanf(songlist, "\n%[^\t]\t%[^\t]\t%d\t%s", record->name, record->singer, &record->year, record->style);
		
		if (feof(songlist)) break;

		if (templist->head == NULL) {

			temp = new song_node;
			temp->data = record;
			temp->next = NULL;
			temp->prev = NULL;
			templist->head = temp;
			templist->songnumber++;
		}
		else if (templist->head->next == NULL) {

			temp = new song_node;
			temp->data = record;
			temp->next = templist->head;
			temp->prev = templist->head;
			templist->head->next = temp;
			templist->head->prev = temp;
			templist->songnumber++;
		}
		else {

			temp = new song_node;
			temp->data = record;
			templist->head->prev->next = temp;
			temp->prev = templist->head->prev;
			templist->head->prev = temp;
			temp->next = templist->head;
			templist->songnumber++;

		}
	}

}

void list::addSong(char* Lname, char* Sname) {

	song_node* tempnode;
	song_node* temp;
	playlist* templist = head;
	
	while (strcmp(templist->name, Lname) != 0 ) { //sarkinin kopyalanacagi listeyi bulma. 

		templist = templist->next;
	}

	tempnode = list::head->next->head; // SORTED list atandi.

	while (strcmp(tempnode->data->name, Sname) != 0) { //kopyalanacak sarkiyi bulma.

		tempnode = tempnode->next;
	}

	if (templist->head == NULL) {
		temp = new song_node;
		temp->data = tempnode->data;
		temp->next = NULL;
		temp->prev = NULL;
		templist->head = temp;
	}
	else if (templist->head->next == NULL) {
		temp = new song_node;
		temp->data = tempnode->data;
		temp->next = templist->head;
		temp->prev = templist->head;
		templist->head->next = temp;
		templist->head->prev = temp;
	}
	else {
		temp = new song_node;
		temp->data = tempnode->data;
		templist->head->prev->next = temp;
		temp->prev = templist->head->prev;
		templist->head->prev = temp;
		temp->next = templist->head;
	}
	templist->songnumber++;
}

void list::playL(char* Lname, char* Sname) {
	playlist* templist = head;
	song_node* tempnode;
	song  info;
	cout << "PLAY >" << endl;

	if (strcmp(Sname, "NONE") == 0 && strcmp(Lname, "NONE") != 0) { // 1. secenek
		while (strcmp(templist->name, Lname) != 0) {
			templist = templist->prev;
			if (strcmp(templist->name, head->name) == 0) { 
				cout << "there is not the list." << endl;
				return;
			}
		}
		tempnode = templist->head;
		info.name = tempnode->data->name;
		info.singer = tempnode->data->singer;
		info.style = tempnode->data->style;
		info.year = tempnode->data->year;
		printPlay(info);
		navigate(tempnode);
	
	}
	else if (strcmp(Sname, "NONE") != 0 && strcmp(Lname, "NONE") != 0) { // 2. secenek

		while (strcmp(templist->name, Lname) != 0) {
			templist = templist->prev;
			if (strcmp(templist->name, head->name) == 0) {
				cout << "there is not the list." << endl;
				return;
			}
		}

		tempnode = templist->head;
		while (strcmp(tempnode->data->name, Sname) != 0) {
			tempnode = tempnode->next;
			if (strcmp(tempnode->data->name, templist->head->data->name) == 0) {
				cout << "there is not the song." << endl;
				return;
			}
		}

		info.name = tempnode->data->name;
		info.singer = tempnode->data->singer;
		info.style = tempnode->data->style;
		info.year = tempnode->data->year;
		printPlay(info);
		navigate(tempnode);
	}
	else if (strcmp(Lname, "NONE") == 0 && strcmp(Sname, "NONE") != 0) { // 3. secenek

		while (strcmp(templist->name, "SORTED") != 0) {
			templist = templist->prev;
			if (strcmp(templist->name, head->name) == 0) {
				cout << "there is not the list." << endl;
				return;
			}
		}

		tempnode = templist->head;
		while (strcmp(tempnode->data->name, Sname) != 0) {
			tempnode = tempnode->next;
			if (strcmp(tempnode->data->name, templist->head->data->name) == 0) {
				cout << "there is not the song." << endl;
				return;
			}
		}

		info.name = tempnode->data->name;
		info.singer = tempnode->data->singer;
		info.style = tempnode->data->style;
		info.year = tempnode->data->year;
		printPlay(info);	
	}

}

void list::navigate(song_node* node) {
	song  info;
	cout << "NEXT(N) - PREVIOUS(P) - EXIT(E)" << endl;
	for (;;) {
		
	switch (getchar()) {
	case 'N': case 'n':
		node = node->next;
		info.name = node->data->name;
		info.singer = node->data->singer;
		info.style = node->data->style;
		info.year = node->data->year;
		printPlay(info);
		cout << "NEXT(N) - PREVIOUS(P) - EXIT(E)" << endl;
		break;
	case 'P': case 'p':
		node = node->prev;
		info.name = node->data->name;
		info.singer = node->data->singer;
		info.style = node->data->style;
		info.year = node->data->year;
		printPlay(info);
		cout << "NEXT(N) - PREVIOUS(P) - EXIT(E)" << endl;
		break;
	case 'E': case 'e':
		return;
		break;
	default:
		break;
	}
}
}

bool list::isfinished() {

	if (feof(songlist)) return true;
	char k[6];
	fscanf(songlist, "\n%s", k);
	if (feof(songlist)) return true;
	if (strcmp(k, "*****") == 0) return false;
	else return true;
}

bool list::deleteList(char* selection) {
	playlist* templist, * tail;
	song_node* tempsong;
	templist = head;
	while (strcmp(templist->name, selection) != 0) {
		tail = templist;
		templist = templist->prev;
		if (strcmp(templist->name, head->name) == 0) { return true; }
	}
	tempsong = templist->head;

	while (templist->songnumber != 0) {
		templist->head = templist->head->next;
		delete tempsong;
		tempsong = templist->head;
		templist->songnumber--;
	}
	tail->prev = templist->prev;
	templist->prev->next = tail;
	delete templist;
	playlist_count--;
	return false;
}

bool list::print(char* selection) {

	playlist* templist;
	song_node* tempnode;
	templist = head;

	while (strcmp(templist->name, selection) != 0 ) {
		templist = templist->prev;
		if (strcmp(templist->name, head->name) == 0) { return true; }
	}
	tempnode = templist->head;
	do {
		cout << tempnode->data->name << "\t" << tempnode->data->singer << "\t" << tempnode->data->year << "\t" << tempnode->data->style << endl;
		tempnode = tempnode->next;
	
	} while (tempnode != templist->head);
	
	return false;
}

bool list::removeSong(char* select_list, char* select_song) {

	playlist* templist;
	song_node* tempsong, *tail;
	templist = head->prev;

	while (strcmp(templist->name, select_list) != 0) {
		
		templist = templist->prev;	
	}
	tempsong = templist->head;
	while (strcmp(tempsong->data->name, select_song ) != 0) {
		
		tail = tempsong;
		tempsong = tempsong->next;
		if (tempsong == templist->head) return false; // boyle bir sarki yok.
	}

	tail->next = tempsong->next;
	tempsong->next->prev = tail;
	delete tempsong;
	return true;
	templist->songnumber--;
}

void list::writeToFile() {

	playlist* templist;
	song_node* tempsong;

	templist = head;
	tempsong = head->head;
	if (!(songlist = fopen(filename, "w+"))) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	do {
		fprintf(songlist, "%s\t%s\t%d\t%s\n", tempsong->data->name, tempsong->data->singer, tempsong->data->year, tempsong->data->style);
		tempsong = tempsong->next;
	} while (tempsong != head->head);

	templist = templist->prev;
	while (strcmp(templist->name, "RANDOM") != 0) {

		tempsong = templist->head;

		fprintf(songlist, "%s\n", "*****");
		fprintf(songlist, "%s\n", templist->name);

		do {
			fprintf(songlist, "%s\t%s\t%d\t%s\n", tempsong->data->name, tempsong->data->singer, tempsong->data->year, tempsong->data->style);
			tempsong = tempsong->next;
		} while (tempsong != templist->head);

		templist = templist->prev;
	}
	fclose(songlist);
}

void list::makeEmpty() {

	playlist* templist;
	song_node* tempsong;

	while (playlist_count != 0) {	
		templist = head;
		head = head->next;
		tempsong = templist->head;
		while (templist->songnumber != 0) {			
			templist->head = templist->head->next;
			delete tempsong;
			tempsong = templist->head;
			templist->songnumber--;
		}
		delete templist;
		playlist_count--;
	}
	playlist_count = 0;
}
