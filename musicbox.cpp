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
#include "musicbox.h"
#include "list.h"
#include "node_structs.h"


using namespace std;

list LIST;

int main(void) {

	char choice = 'k';
	LIST.status = NOTSTARTED;
	LIST.createList(&choice);
	while (LIST.status != FINISHED) {
		mainMenu_print();
		cin >> choice;
		mainFunctions(choice);
	}
	return EXIT_SUCCESS;
}

void mainMenu_print() {
	
	cout << "SONG BOX APPLICATION (USING DOUBLY, CIRCULAR MULTI LINKED LIST) by B.KorayOZ" << endl;
	cout << "Choose an operation" << endl;
	cout << "P: Play" << endl;
	cout << "L: Show all playlists" << endl;
	cout << "A: Add songs to a playlist" << endl;
	cout << "R: Remove songs from a playlist" << endl;
	cout << "C: Create a new playlist" << endl;
	cout << "D: Delete a playlist" << endl;
	cout << "W: Write to file (SAVE)" << endl;
	cout << "E: Exit" << endl;
	cout << endl;
	cout << "The program is case-sensitive. Use only upper-case letters when entering commands!!!" << endl << endl;
	cout << "Enter a choice ( P, L, A, R, C, D, W, E ):";

}

void mainFunctions(char operation) {
	
	switch (operation) {
	case 'P': case 'p':
		play();
		break;
	case 'L': case 'l':
		printList();
		break;
	case 'A': case 'a':
		addSong();
		break;
	case 'R': case 'r':
		removeSong();
		break;
	case 'C': case 'c':
		createList();
		break;
	case 'D': case 'd':
		deleteList();
		break;
	case 'W': case 'w':
		writeToFile();
		break;
	case 'E': case 'e':
		exit();
		break;
	default:
		cout << endl << "Wrong choice! Try again!" << endl;
		break;
	}

}

void createList() {
	char nameL[LNAME_LENGTH];
	char choice;
	createMenu_print();
	cin >> choice;
	cout << "Enter the name of the new playlist :";
	cin.ignore(1000, '\n');
	cin.getline(nameL, LNAME_LENGTH);
	LIST.createList(nameL);
	LIST.full_user(choice);
	cout << "The list named " << nameL << " created." << endl;
}

void addSong() {

	if (LIST.playlist_count == 3) {
		cout << "There is not available playlist you can add a new song." << endl;
		return;
	}	
	char Lname[LNAME_LENGTH];
	char Sname[SNAME_LENGTH];

	cout << "Enter the name of the song you want to add :";
	cin.ignore(1000, '\n');
	cin.getline(Sname, SNAME_LENGTH);
	cout << "Enter the name of the playlist to add the song. ";
	cout << "WARNING! You cannot add a song to the default playlists." << endl;
	cin.getline(Lname, LNAME_LENGTH);
	if (strcmp(Lname, "CHRONOLOGICAL") == 0 || strcmp(Lname, "SORTED") == 0 || strcmp(Lname, "RANDOM") == 0) {	
		cout << "You are trying to add a song to a default list." << endl;
		return;
	}
	LIST.addSong(Lname, Sname);
	cout << "Song named " << Sname << " is added to the list named " << Lname << endl;
}

void play() {

	char Lname[LNAME_LENGTH] = "NONE";
	char Sname[SNAME_LENGTH] = "NONE";
	char choice;
	cout << "1: Play a playlist start from first song." << endl;
	cout << "2: Play a playlist starting from a specific song." << endl;
	cout << "3: play a single song." << endl;
	cout << "Enter your selection: ";
	cin >> choice;
	cout << endl;
	switch (choice) {
	case '1':
		doList();
		cout << "Enter the name of the playlist that you want to play:" << endl;
		cin.ignore(1000, '\n');
		cin.getline(Lname, LNAME_LENGTH);
		LIST.playL(Lname, Sname);
		break;
	case '2':
		doList();
		cout << "Enter the name of the playlist that you want to play:" << endl;
		cin.ignore(1000, '\n');
		cin.getline(Lname, LNAME_LENGTH);
		cout << endl;
		if (LIST.print(Lname)) {
			cout << "There is not a playlist named " << choice << endl;
			return;
		}
		cout << endl << "Enter the name of the song you want to start to play:" << endl;
		cin.getline(Sname, SNAME_LENGTH);
		LIST.playL(Lname, Sname);
		break;
	case '3':
		LIST.print("SORTED");
		cout << "Enter the name of the song that you want to play:" << endl;
		cin.ignore(1000, '\n');
		cin.getline(Sname, SNAME_LENGTH);
		LIST.playL(Lname, Sname);
		break;
	default:
		break;
	}
}

void printPlay(song song) {
	
	cout << "playing . . ." << endl;
	cout << song.name << "\t"<< song.singer << "\t" << song.year << "\t" << song.style << endl;
}

void removeSong() {
	
	char choice[LNAME_LENGTH];
	char choice2[SNAME_LENGTH];
	if (LIST.playlist_count == 3) {
		cout << "There is not avaible playlist to remove a song from." << endl;
		return;
	}
	doList();
	cout << "Enter the name of the playlist you want to remove a song from." << endl;
	cout <<" It is not allowed to remove a song from default playlists. :";
	cin.ignore(1000, '\n');
	cin.getline(choice, LNAME_LENGTH);
	if (strcmp(choice, "CHRONOLOGICAL") == 0 || strcmp(choice, "SORTED") == 0 || strcmp(choice, "RANDOM") == 0) {
		cout << "You are trying to remove a song from a default list." << endl;
		return;
	}
	if (LIST.print(choice)) {
		cout << "There is not a playlist named " << choice << endl;
		return;
	}
	cout << endl << "Enter the name of the song you want to remove :";
	cin.getline(choice2, SNAME_LENGTH);
	if (LIST.removeSong(choice, choice2)) {
		cout << "The song is removed from the list" << endl;
	}
	else {
		cout << "There is not a song named " << choice2 << endl;
	}
}

void deleteList() {

	char choice[LNAME_LENGTH];
	if (LIST.playlist_count == 3) {
		cout << "There is not an avaible playlist to be deleted." << endl;
		return;	
	}
	doList();
	cout << "Enter the name of the playlist you want to delete. Default playlist are not deletable. :";
	cin.ignore(1000, '\n');
	cin.getline(choice, LNAME_LENGTH);
	
	if (strcmp(choice, "CHRONOLOGICAL") == 0 || strcmp(choice, "SORTED") == 0 || strcmp(choice, "RANDOM") == 0) {
		cout << "You are trying to delete a default list." << endl;
		return;
	}

	if (LIST.deleteList(choice)) {
		cout << "There is not a playlist named "<< choice << endl;
	}
	else {
		cout << "Playlist " << choice << " is deleted." << endl;
	}
}

void printList() {
	playlist* templist = LIST.head;

	doList();
	cout << endl;	
	cout << templist->name << endl;
	LIST.print(templist->name);
	cout << "NEXT(N) - PREVIOUS(P) - SELECT the playlist to PLAY, DELETE, ADD a SONG or REMOVE a SONG(S) -  EXIT(E) :";
	cout << endl;
	for (;;) {
		switch (getchar()) {
		case 'N': case 'n':
			templist = templist->next;		
			cout << templist->name << endl;
			LIST.print(templist->name);
			cout << endl;
			cout << "NEXT(N) - PREVIOUS(P) - SELECT the playlist to PLAY, DELETE, ADD a SONG or REMOVE a SONG(S) -  EXIT(E) :" << endl;
			break;
		case 'P': case 'p':
			templist = templist->prev;			
			cout << templist->name << endl;
			LIST.print(templist->name);
			cout << endl;
			cout << "NEXT(N) - PREVIOUS(P) - SELECT the playlist to PLAY, DELETE, ADD a SONG or REMOVE a SONG(S) -  EXIT(E) :" << endl;
			break;
		case 'S': case 's':
			editList(templist->name, &templist);
			cout << templist->name << endl;
			cout << "NEXT(N) - PREVIOUS(P) - SELECT the playlist to PLAY, DELETE, ADD a SONG or REMOVE a SONG(S) -  EXIT(E) :" << endl;
			break;
		case 'E': case 'e':
			return;
			break;
		default:
			break;
	}
}
}

void editList(char* Lname, playlist** ptr) {

	char Sname[SNAME_LENGTH];
	cout << "PLAY(P) - DELETE the LIST(D) - ADD a SONG (A) - REMOVE a SONG(R) -  EXIT(E) :" << endl;
	char choice;
	cin >> choice;
	switch (choice) {
	case 'D': case 'd':
		(*ptr) = (*ptr)->next;
		LIST.deleteList(Lname);
		break;
	case 'A': case 'a':
		addSong();
		cout << endl;
		break;
	case 'R': case 's':
		cout << endl << "Enter the name of the song you want to remove :";	
		cin.getline(Sname, SNAME_LENGTH);
		LIST.removeSong(Lname, Sname);
		break;
	case 'P': case 'p': 
		LIST.playL(Lname, "NONE");
		break;
	case 'E': case 'e':
		return;
		break;
	default:
		break;
	}

}

void doList() { // prints playlist names.

	playlist* templist;
	templist = LIST.head;
	int i = 1;
	cout << "PLAYLISTS :" << endl;
	do {

		cout << i << ": " << templist->name << endl;
		templist = templist->next;
		i++;
	} while (templist != LIST.head);
}

void writeToFile() {
	
	LIST.writeToFile();
	cout << endl << "Current playlists are saved." << endl;
}

void exit() {

	writeToFile();
	LIST.makeEmpty();
	cout << endl << "\tGOOD BYE :)" << endl;
	LIST.status = FINISHED;
}

void createMenu_print() {

	cout << "CREATE A NEW PLAYLIST:" << endl;
	cout << "1: Songs from a specific style" << endl;
	cout << "2: Songs of a specific singer" << endl;
	cout << "3: A combination of existing playlists" << endl;
	cout << "4: A combination of existing songs" << endl;
	cout << endl << "Select how you want to create the new list :";
}