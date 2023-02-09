


/* Demo server program for Bible lookup using AJAX/CGI interface
 * By James Skon, Febrary 10, 2011
 * updated by Bob Kasper, January 2020
 * Mount Vernon Nazarene University
 * 
 * This sample program works using the cgicc AJAX library to
 * allow live communication between a web page and a program running on the
 * same server that hosts the web server.
 *
 * This program is run by a request from the associated html web document.
 * A Javascript client function invokes an AJAX request,
 * passing the input form data as the standard input string.
 *
 * The cgi.getElement function parses the input string, searching for the matching 
 * field name, and returing a "form_iterator" oject, which contains the actual
 * string the user entered into the corresponding field. The actual values can be
 * accessed by dereferencing the form iterator twice, e.g. **verse
 *     refers to the actual string entered in the form's "verse" field.
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

/* Required libraries for AJAX to function */
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

// Required file from Project1
#include "Bible.h"
#include "Ref.h"
#include "Verse.h"

int main() {
  /* A CGI program must send a response header with content type
   * back to the web client before any other output.
   * For an AJAX request, our response is not a complete HTML document,
   * so the response type is just plain text to insert into the web page.
   */
  cout << "Content-Type: text/plain\n\n";

  Cgicc cgi;  // create object used to access CGI request data

  // GET THE INPUT DATA
  // browser sends us a string of field name/value pairs from HTML form
  // retrieve the value for each appropriate field name
  form_iterator st = cgi.getElement("search_type");
  form_iterator book = cgi.getElement("book");
  form_iterator chapter = cgi.getElement("chapter");
  form_iterator verse = cgi.getElement("verse");
  form_iterator nv = cgi.getElement("num_verse");

  int chapterNum, bookNum, verseNum, Numv;
  // Convert and check input data
  bool validInput = false;
  if (chapter != cgi.getElements().end()) {
	 chapterNum = chapter->getIntegerValue();
	 if (chapterNum > 150) {
		 cout << "<p>The chapter number (" << chapterNum << ") is too high.</p>" << endl;
	 }
	 else if (chapterNum <= 0) {
		 cout << "<p>The chapter must be a positive number.</p>" << endl;
	 }
	 else
		 validInput = true;
  }

  /* TO DO: OTHER INPUT VALUE CHECKS ARE NEEDED ... but that's up to you! */
  // Most book is 66
  if (book != cgi.getElements().end()) {
	bookNum = book->getIntegerValue();
	if (bookNum > 66) {
		cout << "<p>The book number (" << chapterNum << ") is too high.</p>" << endl;
	}
	 else if (bookNum <= 0) {
		 cout << "<p>The book must be a positive number.</p>" << endl;
		 validInput = false;
	}
	 else {
		 validInput = true;
	 }
 }
  // Most verse is 176
  if (verse != cgi.getElements().end()) {
	verseNum = verse->getIntegerValue();
	 if (verseNum > 176) {
		 cout << "<p>The verse number (" << verseNum << ") is too high.</p>" << endl;
	 }
	 else if (verseNum <= 0) {
		 cout << "<p>The verse must be a positive number.</p>" << endl;
	       	 validInput = false;
	}
	 else {
		 validInput = true;
	}
  }
  // Check the number of verse
  if (nv != cgi.getElements().end()) {
        Numv = nv->getIntegerValue();
         if (Numv > 176) {
                 cout << "<p>The number of verse (" << Numv << ") is too high.</p>" << endl;
         }
         else if (Numv <= 0) {
                 cout << "<p>The numer of verse must be a positive number.</p>" << endl;
                 validInput = false;
        }
         else {
                 validInput = true;
        }
  }

  /* TO DO: PUT CODE HERE TO CALL YOUR BIBLE CLASS FUNCTIONS
   *        TO LOOK UP THE REQUESTED VERSES
   */
  // DAISY
//  int curV = verseNum;			// current verse
//  int finalV = verseNum + (Numv-1);	// final or destination verse
  int count = 0;
  // Create a reference from the numbers;
  Ref ref(bookNum, chapterNum, verseNum);

  // Create Bible object to process the raw text file
  Bible webBible("/home/class/csc3004/Bibles/web-complete");
  Verse verseResult;
  LookupResult result;

  // Look up the first verse base on reference and display the result.
  verseResult = webBible.lookup(ref, result);
  count++;

  if (validInput) {
	cout << "Search Type: <b>" << **st << "</b>" << endl;
	cout << "<p>Your result: \n" << endl;
  }
  else {
	  cout << "<p>Invalid Input: <em>report the more specific problem.</em></p>" << endl;
  }

  if (!(verseResult.getRef() == ref)) {
	ref.displayNonExisted();
	cout << endl;
	exit(2);
  } else {
	cout << "<br><b>" << endl;
	ref.displayBookNameCh();
//	cout << "<br>" << endl;
//	verseResult.display();
	cout << "</b><br>" << **verse << " : " << verseResult.getVerse() << endl;
  }

  // Only apply on multi-verse case, keep looking for the next verse while the curV is less than or equal to the f 
  if (Numv > 1){
        do {
		verseResult = webBible.nextVerse(result);
                count++;
  //              verseResult.display();
		cout << "<br>" << verseResult.getVerseNum() << " : " << verseResult.getVerse(); 
              	cout << "\n" << endl;
        } while (count != Numv);
   }





  /* SEND BACK THE RESULTS
   * Finally we send the result back to the client on the standard output stream
   * in HTML text format.
   * This string will be inserted as is inside a container on the web page, 
   * so we must include HTML formatting commands to make things look presentable!
   */
/*
  if (validInput) {
	cout << "Search Type: <b>" << **st << "</b>" << endl;
	cout << "<p>Your result: "
		 << **book << " " << **chapter << ":" << verseResult.getVerse()
		 << "<em> The " << **nv
		 << " TEST IF IT UPDATE 1</em></p>" << endl;
  }
  else {
	  cout << "<p>Invalid Input: <em>report the more specific problem.</em></p>" << endl;
  }
*/
  return 0;
}
