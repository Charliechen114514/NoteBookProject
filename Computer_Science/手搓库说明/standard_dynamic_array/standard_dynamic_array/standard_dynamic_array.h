#define _CRT_SECURE_NO_WARNINGS 1
#define	OPENUPPOSARR 1
#define OPENUPDEFAULTSIZE 1
#define	QUICKMALLOC 1
//(General Version)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Error Code Meaning
//Program Normally run till the end return NORMAL as 0
//When Error in mallocing Space the program return 1
//when inputing a NULL we returns -1
//when inputing a invalid input we returns -2
//Locations UnFind we returns -3 
//
typedef enum _DynamicFunctionStatues_ {
	DynamicArray_Normal = 0,
	DynamicArray_ERROR_IN_MALLOCING_SPACE = 1,
	DynamicArray_NULL_INPUT = -1,
	DynamicArray_Invalid_Input = -2,
	DynamicArray_UnFind = -3,
	DynamicArray_Invalid_Free = -4
}DynamicArrayFunctionStatues;
//Mybool defined
//
typedef enum _bool_ {
	True = 1,
	False = 0
}Bool;
#define SHOW_ERROR_DynamicArray_NULL_INPUT printf("\nSorry! Your input NULL!\n")
#define SHOW_ERROR_DynamicArray_ERROR_IN_MALLOCING_SPACE printf("\nSorry!Failed to malloc space for your data\n")
#define SHOW_ERROR_DynamicArray_Invalid_Input printf("\nYour input invalid, reject to run functions\n")
#define SHOW_ERROR_DynamicArray_UnFind printf("\nPositions unfind!\n")
#define SHOW_ERROR_DynamicArray_Invalid_Free printf("\nFree the invalid space,reject to run the functions\n")
//this type of int is specifically used in Returning Find Or Unfind.
//Recommmend to be used as a nickname:)
//Can use Find or Unfind to return the result
//
typedef enum _DynamicArray_isFind_ {
	Find = 1,
	Unfind = 0
}DynamicArray_isFind;

//A switch that used in better Print in Dynamic Array!
//Often use OPEN to beautify the control table
//
typedef enum _BetterPrintSwitch_for_dyarr_ {
	Dyarr_OPEN = 1,
	Dyarr_CLOSE = 0
}BetterPrintSwitch_for_dyarr;

//Main Definitions about DynamicArray
//When Programing , not recommend to Change the data directly! 
//
typedef struct _DynamicArray_ {
	void* DataPiece;
	size_t current_size;
	size_t total_usable_size;
	size_t Single_Data_size;
}DynamicArray;

//--------------------------------Default_size_Type--------------------------------------------
//These abstractions are used to reduce the input
//used as Dyarr_Default_TYPE(type_number) to replace the code:sizeof(Typename)*type_number
#if OPENUPDEFAULTSIZE

//Single Type size
//
#define Dyarr_SIGINT sizeof(int)
#define Dyarr_SIGCHAR sizeof(char)
#define Dyarr_SIGFLOAT sizeof(float)
#define Dyarr_SIGDOUBLE sizeof(double)
#define Dyarr_SIG(dataType) sizeof(dataType)

//Mutiply type size
//
#define Dyarr_INT_SIZE(X) sizeof(int)*X
#define Dyarr_CHAR_SIZE(X) sizeof(char)*X
#define Dyarr_FLOAT_SIZE(X) sizeof(float)*X
#define Dyarr_DOUBLE_SIZE(X) sizeof(double)*X
#define Dyarr_TYPE_SIZE(dataType,X) sizeof(dataType)*X

#endif


//-------------------------------------------QuickMalloc----------------------------------------

//As the name goes lol
//
#if QUICKMALLOC 

#define Dyarr_DEFAULT_MALLOC 5
#define MALLOCDYARR(datatype,data_num) (datatype*)malloc(sizeof(datatype)*data_num)

#endif


//----------------------------------------STD_FUNC_AND_INT_TYPE----------------------------------

// Return type of compared functions
//
typedef unsigned int Is_Used_Compared_Int;

// the pointer type of Print !
// When Printing , type :
// MyPrint user_print_function_name(datatype* e1, datatype* e2)
// {
//	print in your way for your data!
// }
//
typedef void(*MyPrint)(void*);

// the pointer type of Making change for the data that has been locates in the Dynamic Array!
// When want to make some change, type like this:
// Do_Specific_Change user_dochange_function_name(datatype* e1, datatype* e2)
//{
//	do some change here for your data!
//}
//
typedef void* (*Do_Specific_Change)(void*);

// the pointer type of using when comparing for your data
// When want to make a comparisons, type like this:
// CompareFunc user_comp_function_name(datatype* e1, datatype* e2)
//{
//	return //the wishing compare!//
//}
//
typedef Is_Used_Compared_Int(*CompareFunc)(void*, void*);

// the pointer type of using when checking iflocated for your data
// When want to make a comparisons, type like this:
// LocateFunc user_loc_function_name(datatype* e1, datatype* e2)
//{
//	return data1==data2(define by yourself! if complicated, just return Find or unfind to show whether is found)
//}
//
typedef Is_Used_Compared_Int(*LocateFunc)(void*, void*);


//-----------------------Position_Stored_Dynamic_Array_For_Dyarr---------------------------------
#if OPENUPPOSARR
//Main data structure!
//Used in returning multitude locations
//
typedef struct _Dyarrposarr_ {
	int* posSpace;
	size_t pos_size;
}Position_Stored_Dynamic_ArrayFordyarr;

//Want a better Print to beutify your control table? try this one
//
typedef enum _BetterPrintSwitch_for_pos_dyarr_ {
	PSDA_dyarr_OPEN = 1,
	PSDA_dyarr_CLOSE = 0
}BetterPrintSwitch_for_pos_dyarr;

//can use this type when indicating the type
//
typedef unsigned int BetterPrintfor_PosDyarr;

//About Position_Stored_Dynamic_Array_Func
//Create A Position_Stored_Dynamic_Array! Can init it in this way:
//>>Position_Stored_Dynamic_ArrayFordyarr* Name=Init_A_Postion_Stored_Dynamic_ArrayFordyarr();
//
Position_Stored_Dynamic_ArrayFordyarr* Init_A_Postion_Stored_Dynamic_ArrayFordyarr();
//About Positions_Stored_Dynamic_Array
//this function is aimed to output a series of locations that is stored in the pos
////Use PSDA_dyarr_OPEN to have a better shown ,else use PSDA_dyarr_CLOSE
//
DynamicArrayFunctionStatues Show_All_Locations_In_PSDAfor_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr*	posarr, 
	BetterPrintfor_PosDyarr					Whether_Better_Print
);
//About Positions_Stored_Dynamic_Array
//this function is aimed to push back a position into the Position_Stored_Dynamic_ArrayFordyarr
//
DynamicArrayFunctionStatues Push_back_a_locations_in_PSDA_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr*			posarr, 
									   int			pos_acquired
);
//About Positions_Stored_Dynamic_Array
//this function is aimed to return the number of locations
//Use PSDA_dyarr_OPEN to have a better shown ,else use PSDA_dyarr_CLOSE
//
size_t Get_pos_size_From_PSDA_for_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr*			posarr, 
	BetterPrintfor_PosDyarr							Whether_Shown_Print
);
//About Positions_Stored_Dynamic_Array
//Erase a dynamic Array when donot using it!
//
DynamicArrayFunctionStatues DesTroy_A_PSDA_for_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr*			pointer_to_wishedfreeposarr
);
#endif

//----------------------------------DynamicArray----------------------------------------------------------------------
//About Dynamic Array
//A Properway to init a default and empty Dynamic Array
//Use like this: DynamicArray* Dyarr = Init_A_DynamicArray(expected_number, datasize)
//
DynamicArray* Init_A_DynamicArray(
	size_t					expected_number, 
	size_t					datasize
);
//About Dynamic Array
//Copied up a Dyarr!
//Use like this: DynamicArray* copied_one = Init_A_DynamicArray_by_CopyADyarr(be_copied)
//
DynamicArray* Init_A_DynamicArray_by_CopyADyarr(
	DynamicArray*			dyarr_copied
);
//About Dynamic Array
//An update! used to transform a static array to DynamicArray
//use like this:  
//DynamicArray* update_arr = Updata_A_Static_Array_To_Dynamic_Array(
//static arr,
//sizeof(data),
//how_many_data_are_there_in_the_static_array)
//
DynamicArray* Updata_A_Static_Array_To_Dynamic_Array(
	void*						data, 
	size_t						datasize, 
	size_t						datanum
);
//About Dynamic Array
//Push back a data into the Dynamic Array
//Use like this: Push_Back_Into_A_Dynamic_Array(dyarr,data)
//
DynamicArrayFunctionStatues Push_Back_Into_A_Dynamic_Array(
	DynamicArray*				dyarr, 
	void*						data
);
//About Dynamic Array
//Push back a lot of data that has a organization that has all the same data
//Use like this: 
//Push_back_Same_data_Into_A_Dynamic_Array(dyarr,data,the_time_data_repeated,sizeof(data))
//
DynamicArrayFunctionStatues Push_back_Same_data_Into_A_Dynamic_Array(
	DynamicArray*				dyarr, 
	void*						data, 
	size_t						n_repeat, 
	size_t						datasize
);
//About Dynamic Array
//Push back a lot of data that has a organization that has a organiztion with static array
//Use like this: 
//Push_back_Same_data_Into_A_Dynamic_Array(
//dyarr,
//data,
//how_many_data_are_there_in_static_array,
//sizeof(data))
//
DynamicArrayFunctionStatues Push_Back_Some_data_Into_A_Dynamic_Array(
	DynamicArray*				dyarr, 
	void*						data_array, 
	size_t						array_num, 
	size_t						pos, 
	size_t						data_inarray_size
);
//About Dynamic Array
//Reshape the dynamic array
//NOT ROCOMMEND TO USE UNLESS YOU ARE CONCIOUS OF WHAT YOU ARE DOING
//
DynamicArrayFunctionStatues Resize_The_Dynamic_Array(
	DynamicArray*				dyarr, 
	size_t						wished_new_space_size
);
// About Dynamic Array
// Insert back a data 
// use like this: 
// Insert_Into_A_Dynamic_Array(
// dyarr, 
// data, 
// where_to_insert,
//
DynamicArrayFunctionStatues Insert_Into_A_Dynamic_Array(
	DynamicArray*				dyarr, 
	void*						data, 
	size_t						pos
);

//About Dynamic Array
//Insert back a lot of data that has a organization that has all the same data
//Use like this: 																		
//insert_back_Same_data_Into_A_Dynamic_Array(dyarr,n_repeat,datasize,pos)
//
DynamicArrayFunctionStatues insert_back_Same_data_Into_A_Dynamic_Array(
	DynamicArray* dyarr,
	void* data,
	size_t												n_repeat,
	size_t												datasize,
	size_t												pos
)
//About Dynamic Array
//Insert back some data that organized in static array
//use like this: Insert_Into_A_Dynamic_Array(
// dyarr, 
// where_to_insert, 
// data, 
// how_many_data_are_there_in_static_array,
// sizeof(data)
//)
//
DynamicArrayFunctionStatues Insert_Some_Data_Into_A_Dynamic_Array(
	DynamicArray*				dyarr, 
	size_t						pos, 
	void*						data_array, 
	size_t						array_num, 
	size_t						data_inarray_size
);
//About Dynamic Array
//Append another dynamic Array
// use like this:
// AppendByMergeDynamicArray(dyarr_be_appended, exp_append_array)
//
DynamicArrayFunctionStatues AppendByMergeDynamicArray(
	DynamicArray*				dyarr_be_appended, 
	DynamicArray*				exp_append_array
);
//About Dynamic Array
//Gain a copy of targeted array from the dynamic array
//use like this
// type* datawanna = Copy_A_Specific_DataFrom_A_Dynamic_Array_bypos(dyarr, datawanna, sizeof(datawanna))
//
void* Copy_A_Specific_DataFrom_A_Dynamic_Array_bypos(
	DynamicArray*				dyarr, 
	size_t						pos, 
	void*						container, 
	size_t						container_size
);

// About Dynamic Array
// Actually erase the final element!
// use like this:
// Pop_Out_From_A_Dynamic_Array(dyarr)
//
DynamicArrayFunctionStatues Pop_Out_From_A_Dynamic_Array(
	DynamicArray*				dyarr
);

// About Dynamic Array
// Actually erase the final element!
// use like this:
// Pop_Out_From_A_Dynamic_Array(dyarr)
//
DynamicArrayFunctionStatues Pop_Out_From_A_Dynamic_Array(
	DynamicArray*				dyarr
);

// About Dynamic Array
// Actually erase all elements!
// use like this:
// Clear_A_Dynamic_Array(dyarr)
//
DynamicArrayFunctionStatues Clear_A_Dynamic_Array(
	DynamicArray*				dyarr
);
// About Dynamic Array
// Actually erase all elements! and unable to be used again!
// use like this:
// Destroy_A_Dynamic_Array(dyarr)
//
DynamicArrayFunctionStatues Destroy_A_Dynamic_Array(
	DynamicArray*				dyarr
);
// About Dynamic Array
// Actually Print All data
// use like this
// Print_ALL_Data_In_A_Dynamic_Array(dyarr,user_print_funtional_pointer, Dyarr_OPEN or Dyarr_ClOSE)
//
DynamicArrayFunctionStatues Print_ALL_Data_In_A_Dynamic_Array(
	DynamicArray*				dyarr, 
	MyPrint						user_print, 
	BetterPrintSwitch_for_dyarr whether_better_print
);
// About Dynamic Array
// Actually Print a specific data
// use like this
//Print_Specific_Data_In_A_Dynamic_Array(dyarr, user_print, pos)
//
DynamicArrayFunctionStatues Print_Specific_Data_In_A_Dynamic_Array(
	DynamicArray*				dyarr,
	MyPrint						user_print, 
	size_t						pos
);
// About Dynamic Array
// Actually make some change in all data
// use like this
// Do_Specific_Change_To_All_Data(dyarr, user_print, pos)
//
DynamicArrayFunctionStatues Do_Specific_Change_To_All_Data(
	DynamicArray*				dyarr, 
	Do_Specific_Change			user_change
);
// About Dynamic Array
// Actually make some change in a specific data
// use like this
// Do_Specific_Change_To_All_Data(dyarr, user_print, pos)
//
DynamicArrayFunctionStatues Do_Specific_Change_To_Specific_Data(
	DynamicArray*				dyarr, 
	Do_Specific_Change			user_change, 
	size_t						pos
);
// About Dynamic Array
// Actually erase a specific data by pos
// use like this
// Delete_A_Specific_Data_From_the_DynamicArray(dyarr,  pos)
//
DynamicArrayFunctionStatues Delete_A_Specific_Data_From_the_DynamicArray(
	DynamicArray*				dyarr, 
	size_t						pos
);
// About Dynamic Array
// Actually erase some specific data by pos
// use like this
// Delete_A_Specific_Data_From_the_DynamicArray(dyarr, beginpos, endpos)
//
DynamicArrayFunctionStatues Delete_Some_Specific_Data_From_the_DynamicArray(
	DynamicArray*				dyarr, 
	size_t						Beginpos, 
	size_t						Endpos
);
// About Dynamic Array
// Actually erase a specific data by pos
// use like this
// Delete_A_Specific_Data_From_the_DynamicArray(dyarr,  pos)
//
DynamicArrayFunctionStatues reverse_Data_In_DynamicArray(
	DynamicArray*				dyarr
);
//
// About Dynamic Array
// this is used in judging whether the dynamic array is empty
// use like this:
// isEmpty_InDynamicArray(dyarr)
//
Bool isEmpty_InDynamicArray(
	DynamicArray*				dyarr
);
// About Dynamic Array
// this is used in swap data
// use like this:
// swapData_in_DynamicArray(dyarr,pos1,pos2)
//
DynamicArrayFunctionStatues swapData_in_DynamicArray(
	DynamicArray*				dyarr, 
	size_t						pos1, 
	size_t						pos2
);
// About Dynamic Array
// sadly that is bubblesort :(
// I haven't make it in quicksort as it was toooooooooooooooooooooo tiring lol
// use like this:
// sort_In_Dynamic_Array(dyarr,comparision_funcuntional_pointer)
//
DynamicArrayFunctionStatues sort_In_Dynamic_Array(
	DynamicArray*				dyarr, 
	CompareFunc					compfunc
);
// About Dynamic Array
// check if located in the dynamic array
// use like this:
// isLocateinDyarr(dyarr, data, comparision_funcuntional_pointer)
//
DynamicArrayFunctionStatues isLocateinDyarr(
	DynamicArray*				dyarr, 
	void*						data, 
	LocateFunc					user_func
);
// About Dynamic Array
// return the position of data that is targeted 
// use like this:
// returnAElembyPos_inDyarr(dyarr, data, comparision_funcuntional_pointer)
//
DynamicArrayFunctionStatues returnAElembyPos_inDyarr(
	DynamicArray*				dyarr, 
	void*						data, 
	LocateFunc					user_func
);
// About Dynamic Array
// Using the function when Posarr is enable to use!
// return a bunch of position of data that is targeted 
// use like this:
// Position_Stored_Dynamic_ArrayFordyarr* pos =r eturnAElembyPos_inDyarr(dyarr, posArr,data, comparision_funcuntional_pointer)
//
#if OPENUPPOSARR
Position_Stored_Dynamic_ArrayFordyarr* returnABunchofData_inDyarr(
	DynamicArray*				dyarr, 
	Position_Stored_Dynamic_ArrayFordyarr* posArr, 
	void*						data, 
	LocateFunc					user_func
);
#endif