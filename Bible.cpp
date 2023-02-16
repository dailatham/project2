// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
}

// Constructor – pass bible filename
Bible::Bible(const string s) {	infile = s;}

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status) { 
    // update the status variable
    status = OTHER; // placeholder until retrieval is attempted
    // create and return the verse object
    Verse aVerse;	// default verse, to be replaced by a Verse object
	                // that is constructed from a line in the file.


    // TODO: scan the file to retrieve the line that holds ref ...
    // DAISY
    instream.open(infile.c_str(), ios::in);
    string s;
    Verse verse;
    Ref cur;
    bool bookFound = false, chapFound = false, verseFound = false;

    do {
	// get a next verse
	getline(instream, s);
		if (s != ""){
		verse = Verse(s);
		cur = verse.getRef();

		// check if the current book, chapter, verse exist.
		if (cur.getBook() == ref.getBook())
			bookFound = true;
		if (cur.getBook() == ref.getBook() && cur.getChap() == ref.getChap())
			chapFound = true;
		if (cur.getBook() == ref.getBook() && cur.getChap() == ref.getChap() && cur.getVerse() == ref.getVerse())
			verseFound == true;

		// check if the retreive verse match the ref
		if (verse.getRef() == ref){
			aVerse = verse;
			status = SUCCESS;
		}
		}
    } while (!(verse.getRef() == ref) && !instream.fail());

    // update th status
    if (status != SUCCESS) {
	if (bookFound && chapFound) { status = NO_VERSE; }
	else if (bookFound){ status = NO_CHAPTER; }
	else { status = NO_BOOK; }
    }

    return(aVerse);
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status) {
	Verse verse;
	Ref ref1 = Ref(1,1,1);
	string s;

	if (!instream){
		instream.open(infile.c_str(), ios::in);
		verse = lookup(ref1, status);
		return verse;
	} else {
		getline(instream, s);
		verse = Verse(s);
		return verse;
 	}
}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status) {
	//DAISY
//	cout << "ERROR :  " << status <<  endl;
	if (status == NO_BOOK) {
		return "Error : No book found.";
	}
	else if (status == NO_CHAPTER) {
		return "Error : No chapter found.";
	}
	else if (status == NO_VERSE) {
		return "Error : No verse found.";
	}
	else if (status == OTHER) {
		return "Error : Unspecified";
	}
	else {
		return "!!WHY NOT WORK!!";
	}
}

void Bible::display() {
	cout << "Bible file: " << infile << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref
Ref Bible::next(const Ref ref, LookupResult& status) {}

// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status) {}
