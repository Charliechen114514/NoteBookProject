#define _CRT_SECURE_NO_WARNINGS 1
#include"ClassicLinkList.h"

MyPrint print(int* e) {
	printf("%d ", *e);
}

Do_Specific_Change dochange(int* e) {
	*e = *e + 1;
}

LocateFunc loc(int* e1, int* e2) {
	return *e1 == *e2;
}

CompareFunc comp(int* e1, int* e2) {
	return *e1 < *e2;
}
int main()
{
	//do test initailization

	//default init
	Classic_DataList* defaultinit = Init_A_ClassicLinkList();

	//updata init

	int array[10] = { 1,2,3,4,5,6,7,8,9,10 };
	Classic_DataList* update_one = UpdateStaticArray2ClassicLinkList(array, Dyarr_SIGINT, 10);
	Print_All_Data_LinkList(update_one, print, ClassicLinkList_OPEN);

	// copy init

	Classic_DataList* copy_one = Init_A_ClassicLinkList_By_CopyAClassicLinkList(update_one);
	printf("\nThouth , this is the copy one:");
	Print_All_Data_LinkList(copy_one, print, ClassicLinkList_OPEN);






	// Push back 
	int addersig = 100;
	printf("\nFirst push:");
	Push_Back_Into_A_ClassicLinkList(defaultinit, &addersig, Dyarr_SIGINT);
	Print_All_Data_LinkList(defaultinit, print, ClassicLinkList_OPEN);
	printf("\nSecond push:");
	Push_Back_Into_A_ClassicLinkList(defaultinit, &addersig, Dyarr_SIGINT);
	Print_All_Data_LinkList(defaultinit, print, ClassicLinkList_OPEN);

	// Push back a sum
	int adderarr[5] = { 101,102,103,104,105 };
	push_Back_BunchDataintoClassicLinkList(defaultinit, adderarr, Dyarr_SIGINT, 5);
	Print_All_Data_LinkList(defaultinit, print, ClassicLinkList_OPEN);

	//Insert start:
	int insertionsig = -100;

	//to the head:
	Insert_into_AClassicLinkList(defaultinit, &insertionsig, Dyarr_SIGINT, 0);
	Print_All_Data_LinkList(defaultinit, print, ClassicLinkList_OPEN);

	//to other place
	Insert_into_AClassicLinkList(defaultinit, &insertionsig, Dyarr_SIGINT, 1);
	Print_All_Data_LinkList(defaultinit, print, ClassicLinkList_OPEN);

	//for a bunch ...
	//head
	int insertarr[5] = { -1,-2,-3,-4,-5 };
	Insert_A_Bunch_of_data_intoClassicLinkList(update_one, 0, insertarr, Dyarr_SIGINT, 5);
	Print_All_Data_LinkList(update_one, print, ClassicLinkList_OPEN);

	//other place
	Insert_A_Bunch_of_data_intoClassicLinkList(update_one, 1, insertarr, Dyarr_SIGINT, 5);
	Print_All_Data_LinkList(update_one, print, ClassicLinkList_OPEN);

	//Erase 
	eraseAElementfromDataList(copy_one, 0);
	Print_All_Data_LinkList(copy_one, print, ClassicLinkList_OPEN);

	eraseAElementfromDataList(copy_one, 1);
	Print_All_Data_LinkList(copy_one, print, ClassicLinkList_OPEN);

	//Erase bunch
	eraseAbunchData_inDataList(copy_one, 0, 2);
	Print_All_Data_LinkList(copy_one, print, ClassicLinkList_OPEN);


	//make change:
	//sig
	doChangetoSpecificElementinLinkList(copy_one, 0, dochange);
	Print_All_Data_LinkList(copy_one, print, ClassicLinkList_OPEN);

	//interval
	doChangetoTargetIntervalDatainLinkList(copy_one, 0, 2, dochange);
	Print_All_Data_LinkList(copy_one, print, ClassicLinkList_OPEN);

	//all
	doChangetoAllDatainLinkList(copy_one, dochange);
	Print_All_Data_LinkList(copy_one, print, ClassicLinkList_OPEN);

	//check if in
	Classic_DataList* checkerlist = UpdateStaticArray2ClassicLinkList(insertarr, Dyarr_SIGINT, 5);
	int wannafind = -1;
	printf("So is it null?");
	if (!isEmptyClassicLinkList(checkerlist)) {
		printf("\nNot null sir!\n");
	}
	if (checkIsLocateinLinkList(checkerlist, &wannafind, loc)) {
		printf("yes, there is a num that is -1\n");
	}
	printf("and it is on the place: %d\n", returnOutDatabyposinLinkList(checkerlist, &wannafind, loc));
	int wannafind2 = wannafind - 1;
	printf("and also there is -2 too, it is in: %d\n", returnOutDatabyposinLinkList(checkerlist, &wannafind2, loc));
	printf("I can also make a change in this way directly:\n");
	doChangetoSpecificElementinLinkList(checkerlist, returnOutDatabyposinLinkList(checkerlist, &wannafind2, loc), dochange);
	Print_All_Data_LinkList(checkerlist, print, ClassicLinkList_OPEN);

	//find bunch 
	Position_Stored_Dynamic_ArrayFordyarr* posarr = Init_A_Postion_Stored_Dynamic_ArrayFordyarr();
	returnAbunchLocationsinLinkList(checkerlist, posarr, &wannafind, loc);
	Show_All_Locations_In_PSDAfor_dyarr(posarr, PSDA_dyarr_OPEN);

	//reverse
	ReverseLinkList(checkerlist);
	Print_All_Data_LinkList(checkerlist, print, ClassicLinkList_OPEN);

	//Sort
	sortClassicLinkListinBubbleSort(checkerlist, comp);
	Print_All_Data_LinkList(checkerlist, print, ClassicLinkList_OPEN);

	//Del
	clearAClassicLinkList(checkerlist);
	Print_All_Data_LinkList(checkerlist, print, ClassicLinkList_OPEN);
}
