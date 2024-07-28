#define _CRT_SECURE_NO_WARNINGS 1
#include"standard_dynamic_array.h"
MyPrint print(int* e1) {
	printf("%d ", *e1);
}
Do_Specific_Change dochange(int* e1) {
	*e1 = *e1 + 1;
}
LocateFunc loc(int* e1, int* e2) {
	if (*e1 == *e2) {
		return Find;
	}
	return Unfind;
}
int main()
{
	int data1 = 10;
	//test Initing
	DynamicArray* testDyarr1 = Init_A_DynamicArray(10, Dyarr_SIGINT);
	//test a Sigdata pushed:
	Push_Back_Into_A_Dynamic_Array(testDyarr1, &data1);
	Print_ALL_Data_In_A_Dynamic_Array(testDyarr1, print, Dyarr_OPEN);
	//test pushing the same data
	Push_back_Same_data_Into_A_Dynamic_Array(testDyarr1, &data1, 10, Dyarr_SIGINT);
	Print_ALL_Data_In_A_Dynamic_Array(testDyarr1, print, Dyarr_OPEN);
	//Test Clearing
	Clear_A_Dynamic_Array(testDyarr1);
	Print_ALL_Data_In_A_Dynamic_Array(testDyarr1, print, Dyarr_OPEN);
	//test update
	int data2[10] = { 1,2,3,4,5,6,7,8,9,10 };
	DynamicArray* test2=Updata_A_Static_Array_To_Dynamic_Array(data2, Dyarr_SIGINT, 10);
	Print_ALL_Data_In_A_Dynamic_Array(test2, print, Dyarr_OPEN);
	//test copy:
	DynamicArray* copyone = Init_A_DynamicArray_by_CopyADyarr(test2);
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	//test insert	
	printf("before:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	Insert_Into_A_Dynamic_Array(copyone, &data1, 1);
	printf("after:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	//test insert bunch
	printf("before:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	Insert_Some_Data_Into_A_Dynamic_Array(copyone, 1, data2, 10, Dyarr_SIGINT);
	printf("after:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	//test Erasing sigone
	printf("before:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	Delete_A_Specific_Data_From_the_DynamicArray(copyone, 1);
	printf("after:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	//test Erasing bunch one
	printf("before:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	Delete_Some_Specific_Data_From_the_DynamicArray(copyone,1,10);
	printf("after:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	//test Do change
	printf("before:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	Do_Specific_Change_To_Specific_Data(copyone,dochange,1);
	printf("after:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	printf("before:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	Do_Specific_Change_To_All_Data(copyone, dochange);
	printf("after:");
	Print_ALL_Data_In_A_Dynamic_Array(copyone, print, Dyarr_OPEN);
	//test location:
	DynamicArray* test3 = Updata_A_Static_Array_To_Dynamic_Array(data2, Dyarr_SIGINT, 10);
	if (isLocateinDyarr(test3, &data2[2], loc)) {
		printf("\nI have found it!\n");
	}
	int where = returnAElembyPos_inDyarr(test3, &data2[2], loc);
	printf("\nIn dyarr the %d place\n", where);
	//test Position Stored Dynamic Array and returnBunch
	Clear_A_Dynamic_Array(test3);
	Push_back_Same_data_Into_A_Dynamic_Array(test3, &data2[2], 10, Dyarr_SIGINT);
	Position_Stored_Dynamic_ArrayFordyarr* p1 = Init_A_Postion_Stored_Dynamic_ArrayFordyarr();
	returnABunchofData_inDyarr(test3, p1, &data2[2], loc);
	Print_ALL_Data_In_A_Dynamic_Array(test3, print, Dyarr_OPEN);
	Show_All_Locations_In_PSDAfor_dyarr(p1, PSDA_dyarr_OPEN);
}