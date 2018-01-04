
typedef int (*personProfession)(char*) ;

typedef struct{
	char* name;
	int age;
	personProfession func;
} person;



struct familyTree
{
	int nMembers;
	person p[2];
	struct familyTree* next;
};

typedef struct familyTree FamilyTree_t;


#include <stdio.h>
#include <string.h>
int Refua(char* name) { printf("I'm a doctor\n"); return 0; }
int Handasa(char* name) { printf("I'm an engineer\n"); return 0; }

FamilyTree_t Halakhmi = {2, "Ilan", 28, Handasa, "Gilad", 26, Refua, 0};
FamilyTree_t Levi     = {2, "David", 38, Refua, "Lea", 30, Handasa, 0};

void DoIt(FamilyTree_t* ftPtr, char* name)
{
	int i = 0;
	for (i = 0; i < ftPtr->nMembers; ++i)
	{
		if (strcmp(ftPtr->p[i].name, name))
		{
			ftPtr->p[i].func(name);
		}
	}
}
int main() {
	DoIt(&Halakhmi , "Ilan");
	DoIt(&Levi , "David");
	return 1;
}

