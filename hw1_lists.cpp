#include <fstream>
#include <cstring>
#include <sstream>
#include <iostream>
using namespace std;

struct Item{
	Item(int v, Item* n){val = v; next = n;}
	int val;
	Item* next;
};


void readLists(Item*& head1, Item*& head2, std::ifstream& ifile);

Item* concatenate(Item* head1, Item* head2);

void removeEvens(Item*& head);

double findAverage(Item* head);

void printList(std::ofstream& ofile, Item* head);

void deleteEvens(Item*& head);

int sum(Item* head);

int count(Item* head);

int count(Item* head){
	if(head==NULL)
		return 0;
	else
		return 1.0+count(head->next);
}


int sum(Item* head){
	if(head == NULL)
		return 0;
	else 
		return head->val+sum(head->next);
}


double findAverage(Item* head){
	int s = sum(head);
	double c = count(head);
	double ave = double(s/c);
	return ave;
}

void readLists(Item*& head1, Item*& head2, std::ifstream& ifile){
	stringstream ss;
	int n;
	string ln;
	getline(ifile, ln);
	Item* temp;
	ss<<ln;
	if(ln.empty())
		head1 = NULL;
	else{
		ss>>n;
		head1 = new Item(n, NULL);
		temp = head1;
		while(ss>>n){
			temp->next = new Item(n,NULL);
			temp = temp->next;
		}
	}
	ss.clear();
	getline(ifile, ln);
	ss<<ln;
	if(ln.empty())
		head2 = NULL;
	else{
		ss>>n;
		head2 = new Item(n, NULL);
		temp = head2;
		while(ss>>n){
			temp->next = new Item(n, NULL);
			temp = temp->next;
		}
	}
	return;
}	


Item* concatenate(Item* head1, Item* head2){
	Item* nhead;
	if(head1==NULL)
		nhead=head2;
	else if(head2==NULL)
		nhead=head1;
	else
		nhead = head1;
	if(head1==NULL){
		if(head2==NULL)
			return NULL;
		else
			return new Item(head2->val, concatenate(head1, head2->next));
	}
	else{
		return new Item(head1->val, concatenate(head1->next, head2));
	}
}


void deleteEvens(Item*& head){
	Item* del;
	if(head==NULL)
		return;
	if(head->val%2==0){
		del = head;
		head = head->next;
		delete del;
		deleteEvens(head);
	}
	else if(head->val%2!=0){
		deleteEvens(head->next);
	}
}


void printList(std::ofstream& ofile, Item* head){
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);    
  }
 }

main(int argc, char* argv[]){
	ifstream ifile(argv[1]);
	ofstream ofile(argv[2]);
	Item* head1;
	Item* head2; 
	readLists(head1, head2, ifile);
	//cout<<head1->next->val<<" "<<head2->next->val<<endl;
	Item* head3 = concatenate(head1, head2);
	deleteEvens(head3);
	printList(ofile, head3);
	int ave = findAverage(head3);
	cout<<ave;
	return 0;
}
