#define _CRT_SECURE_NO_WARNINGS 1
#define	OPENUPPOSARR 1
#define OPENUPDEFAULTSIZE 1
#define OPENQUICKMALLOC 1
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
typedef enum _ClassicLinkListFunctionStatues_ {
	ClassicLinkList_NORMAL = 0,
	ClassicLinkList_ERROR_IN_MALLOCING_SPACE = 1,
	ClassicLinkList_NULL_INPUT = -1,
	ClassicLinkList_Invalid_Input = -2,
	ClassicLinkList_UnFind = -3,
	ClassicLinkList_Invalid_Free = -4,
}ClassicLinkListFunctionStatues;

//MyBool Defined here!
//
typedef enum _bool_ {
	True = 1,
	False = 0
}Bool;

//This is some abstractions using in reminding you some basic informations and errors!
//
#define SHOW_ERROR_ClassicLinkList_NULL_INPUT printf("\nSorry! Your input NULL!\n")
#define SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE printf("\nSorry!Failed to malloc space for your data\n")
#define SHOW_ERROR_ClassicLinkList_Invalid_Input printf("\nYour input invalid, reject to run functions\n")
#define SHOW_ERROR_ClassicLinkList_UnFind printf("\nPositions unfind!\n")
#define SHOW_ERROR_ClassicLinkList_Invalid_Free printf("\nFree the invalid space,reject to run the functions\n")
#define SHOW_WARNING_ClassicLinkList_SWAPPED_POS printf("Warning! the front_pos is bigger then the final pos\n Do you agreed swap them?")
#define SHOW_WARNING_ClassicLinkList_OVERLAP_POS printf("Considered as your insertion_input is overlapped!\n set pos as the cur_size?")
//this abstractions is used to define the aquisition of whether the program's decison is acceptable,
//X is the message string!
//
#define SHOW_WHETHER_ACCCEPTED(X) printf(X)

//If wanted flashed a newline you can use it! 
//
#define SLASHN printf("\n")

//used in MergeclassicLinkList
//If accepted copy £¡ Do write ClassicLinkList_ACCEPTED_COPY
#define ClassicLinkList_ACCEPTED_COPY 1
#define ClassicLinkList_NO_COPY	0
#define Unfind_ClassicLinkList -1

//Used in whether the targeted elements is found
//If is considered found, just use Find , otherwise unfind!
typedef enum _ClassicLinkList_isFind_ {
	Find = 1,
	Unfind = 0
}ClassicLinkList_isFind;

//Used in whether print data in ClassicLinkList better
//Use ClassicLinkList_OPEN if you want a better print
typedef enum _BetterPrintSwitch_for_ClassicLinkList_ {
	ClassicLinkList_OPEN = 1,
	ClassicLinkList_CLOSE = 0
}BetterPrintSwitch_for_ClassicLinkList;

//-------------------------------------------Main_Define------------------------------------------

//Basic definitions of datanode, it can be considered as a node in a loop
//is consisted of dataPiece and the pointer to the next datanode
//UNLESS YOU ARE CONCIOUS ABOUT WHAT YOU ARE DOING! DO NOT CHANGE THE DATA DIRECTLY! 
typedef struct _Classic_DataNode_ {
	void* data;
	struct _Classic_DataNode_* p_next_one;
}Classic_DataNode;

//basic definations of datalist , it can be considered as the loop or the main body of the data structure
//to better operate the data structure , it is consisted of Head pointer that pointed to the first data in the data struct
//as well as the current_size of the data structure
//UNLESS YOU ARE CONCIOUS ABOUT WHAT YOU ARE DOING! DO NOT CHANGE THE DATA DIRECTLY! 
typedef struct _Classic_DataList_ {
	Classic_DataNode* Head;
	size_t current_size;
}Classic_DataList;

//this type of int is used to mark the returnType of the compare functions
typedef unsigned int Is_Used_Compared_Int;
typedef void(*MyPrint)(void*);
typedef void* (*Do_Specific_Change)(void*);
typedef Is_Used_Compared_Int(*CompareFunc)(void*, void*);
typedef Is_Used_Compared_Int(*LocateFunc)(void*, void*);

//--------------------Default_size_Type---------------------------------------------
#if OPENUPDEFAULTSIZE


#define Dyarr_SIGINT sizeof(int)
#define Dyarr_SIGCHAR sizeof(char)
#define Dyarr_SIGFLOAT sizeof(float)
#define Dyarr_SIGDOUBLE sizeof(double)
#define Dyarr_SIG(dataType) sizeof(dataType)

#define Dyarr_INT_SIZE(X) sizeof(int)*X
#define Dyarr_CHAR_SIZE(X) sizeof(char)*X
#define Dyarr_FLOAT_SIZE(X) sizeof(float)*X
#define Dyarr_DOUBLE_SIZE(X) sizeof(double)*X
#define Dyarr_TYPE_SIZE(dataType,X) sizeof(dataType)*X

#endif

//-------------------------------QuickMalloc----------------------------------------------------
#if OPENQUICKMALLOC

#define MALLOC(type) (type*)malloc(sizeof(type))
#define MALLOCN(type,ElemNum) (type*)malloc(sizeof(type)*ElemNum)

#endif
//-----------------------Position_Stored_Dynamic_Array_For_Dyarr---------------------------------
//About Position_Stored_Dynamic_Array_Func
//Create A Position_Stored_Dynamic_Array! Can init it in this way:
//>>Position_Stored_Dynamic_ArrayFordyarr* Name=Init_A_Postion_Stored_Dynamic_ArrayFordyarr();
//Used in returning multitude locations

#if OPENUPPOSARR

//Main data structure!
//Used in returning multitude locations

typedef struct _Dyarrposarr_ {
	int* posSpace;
	size_t pos_size;
}Position_Stored_Dynamic_ArrayFordyarr;

//Want a better Print to beutify your control table? try this one

typedef enum _BetterPrintSwitch_for_pos_dyarr_ {
	PSDA_dyarr_OPEN = 1,
	PSDA_dyarr_CLOSE = 0
}BetterPrintSwitch_for_pos_dyarr;

//can use this type when indicating the type

typedef unsigned int BetterPrintfor_PosDyarr;

//About Position_Stored_Dynamic_Array_Func
//Create A Position_Stored_Dynamic_Array! Can init it in this way:
//>>Position_Stored_Dynamic_ArrayFordyarr* Name=Init_A_Postion_Stored_Dynamic_ArrayFordyarr();

Position_Stored_Dynamic_ArrayFordyarr* Init_A_Postion_Stored_Dynamic_ArrayFordyarr();

//About Positions_Stored_Dynamic_Array
//this function is aimed to output a series of locations that is stored in the pos
//Use PSDA_dyarr_OPEN to have a better shown ,else use PSDA_dyarr_CLOSE
//
ClassicLinkListFunctionStatues Show_All_Locations_In_PSDAfor_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr* posarr,
	BetterPrintfor_PosDyarr									Whether_Better_Print
);

//About Positions_Stored_Dynamic_Array
// push back a pos into the dynamic array
//
ClassicLinkListFunctionStatues Push_back_a_locations_in_PSDA_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr* posarr,
	int														pos_acquired
);

//About Positions_Stored_Dynamic_Array
//this function is aimed to return the number of locations
//Use PSDA_dyarr_OPEN to have a better shown ,else use PSDA_dyarr_CLOSE
size_t Get_pos_size_From_PSDA_for_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr* posarr,
	BetterPrintfor_PosDyarr									Whether_Shown_Print
);

//About Positions_Stored_Dynamic_Array
//return a pos that is targeted!
//
void* getPosbyPosinPSDA(
	Position_Stored_Dynamic_ArrayFordyarr* getter,
	size_t												pos
);

//About Positions_Stored_Dynamic_Array
ClassicLinkListFunctionStatues DesTroy_A_PSDA_for_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr* pointer_to_wishedfreeposarr
);

#endif // 	OPENUPPOSARR


//-----------------------------About ClassicLinkList-----------------------------------------------------------

//----------------------------Init-functions--------------------------------------------------------------------
// 
// there are three basic type of initialization
// 
// ------------------------------------------------------------------------------------------------------------
// 1.includeing the default type (init a NULL head and zero cur_size)
// func1: Classic_DataList* Init_A_ClassicLinkList()
// 
// No input , or input VOID
// have output : output a clssicLinklist pointer
// -------------------------------------------------------------------------------------------------------------
// 2.includeing the copy one (init the same type of the be-copied one)
// func2: Classic_DataList* Init_A_ClassicLinkList_By_CopyAClassicLinkList
// 
// input : a required_be_copied list .
// output: a new list but have is the same as the be_copied list
// -------------------------------------------------------------------------------------------------------------
// 3.includeing to transform the static array to the linklist one
// func3: Classic_DataList* UpdateStaticArray2ClassicLinkList
// 
// input : a waited_transformed static_array , the element size which is in the static array 
// output: a new pointer that points to classicLinkList
// 
// 
//----------------------------Init-functions--------------------------------------------------------------------


// About ClassicLinkList
// This function is used to init a default type of classicLinkList
// that the head of dataPiece is NULL and the cur_size is zero.
// Use push back to init the dataPiece
// use in this Way: 
// Classic_DataList* List = Init_A_ClassicLinkList();
//
Classic_DataList* Init_A_ClassicLinkList();

// About ClassicLinkList
// to copy an already exited linklist
// Classic_DataList* List = Init_A_ClassicLinkList_By_CopyAClassicLinkList(Classic_DataList* list) 
//
Classic_DataList* Init_A_ClassicLinkList_By_CopyAClassicLinkList(
	Classic_DataList* list
);


// About ClassicLinkList
// to updata a static array into a ClassicLinkList
// Classic_DataList* List = UpdateStaticArray2ClassicLinkList(
// void* inputArray, 
// size_t dataSize, 
// size_t dataNum
// )
//
Classic_DataList* UpdateStaticArray2ClassicLinkList(
	void* inputArray,
	size_t									dataSize,
	size_t									dataNum
);


//----------------------------------------Basic_Add_Functions--------------------------------------------
// there are four basic input functions:
// 
// ------------------------------------------------------------------------------------------------------
// 1. push back an element into the classicLinkList
// func1 : ClassicLinkListFunctionStatues Push_Back_Into_A_ClassicLinkList
//
// input : the inserted list ,the data wanted to be inserted and the inserted datasize
// output: the statues of normal ,can be used in check or just ignore!
// 
// ------------------------------------------------------------------------------------------------------
// 
// 2. insert back an element into the classicLinkList by offering a valid pos
// func2 : ClassicLinkListFunctionStatues Insert_into_AClassicLinkList(Classic_DataList* list, void* data,size_t dataSize,size_t pos)
// 
// 
// input : the inserted list , the data ,the datasize as well as the position you wanted to insert
// output: the statues of normal ,can be used in check or just ignore!
// 
// ------------------------------------------------------------------------------------------------------
// 
// 3. push back a bunch of data into the classicLinkList like the first function
// func3 :ClassicLinkListFunctionStatues push_Back_BunchDataintoClassicLinkList(Classic_DataList* list,void* inputArray,size_t sigElemSize,size_t arrayNum)
// 
// input : the inserted list , the data ,the datasize as well as the position you wanted to insert
// output: the statues of normal ,can be used in check or just ignore!
// 
// ------------------------------------------------------------------------------------------------------
// 4. insert back a bunch of data into the classicLinkList like the second function
// func4: ClassicLinkListFunctionStatues Insert_A_Bunch_of_data_intoClassicLinkList
//
// input : the inserted list , the static array ,the datasize in the static array as well as the position you wanted to insert
// output: the statues of normal ,can be used in check or just ignore! 
// 
//----------------------------------------Basic_Add_Functions--------------------------------------------

// About ClassicLinkList
// push back some data ,like dynamic array , into the final position
//Used like this Push_Back_Into_A_ClassicLinkList(appendedClassicLinkList, data ,sizeof(data))
//
ClassicLinkListFunctionStatues Push_Back_Into_A_ClassicLinkList(
	Classic_DataList* list,
	void* data,
	size_t														datasize
);

// About ClassicDataList
// insert back a data into the datalist
// used like this: Insert_into_AClassicLinkList(inserted list, input data,dataSize,insertion_pos)
// 
ClassicLinkListFunctionStatues Insert_into_AClassicLinkList(
	Classic_DataList* list,
	void* data,
	size_t													dataSize,
	size_t													pos
);


// About ClassicDataList
// push back a bunch data into the datalist
// used like this : push_Back_BunchDataintoClassicLinkList( inserted_list , the static array ,the elementsize ,the element num)
//
ClassicLinkListFunctionStatues push_Back_BunchDataintoClassicLinkList(
	Classic_DataList* list,
	void* inputArray,
	size_t													sigElemSize,
	size_t													arrayNum
);

// About ClassicDataList
// insert back a bunch of data into the datalist
// used like this: Insert_into_AClassicLinkList(inserted list, insertion_pos,input array ,Single dataSize, the amount of elements)
// 
ClassicLinkListFunctionStatues Insert_A_Bunch_of_data_intoClassicLinkList(
	Classic_DataList* list,
	size_t											pos,
	void* inputArray,
	size_t											sigElemSize,
	size_t											arrayNum
);


//------------------------------------------Deletion_Functions-------------------------------------------------------------
// there are two basic type of functions in the sections
// 1. Erase a targeted element and erase it from the ClassicDataList
// fun1:eraseAElementfromDataList
// 
// input : the list and the erase position
// output: the statues of normal ,can be used in check or just ignore!
// 
// ------------------------------------------------------------------------------------------------------------------------
// 
// 2.Erase some target elements from the ClassicDataList
// fun2:eraseAbunchData
// 
// input: the list and the start position as well as the last position, that means offer a paired pos
// output: the statues of normal ,can be used in check or just ignore!
//------------------------------------------Deletion_Functions-------------------------------------------------------------


// About ClassicDataList
// delete a  data in the datalist by offering a position
//used like this: eraseAElementfromDataList(list, erasing_pos)
//
ClassicLinkListFunctionStatues eraseAElementfromDataList(
	Classic_DataList* list,
	size_t													pos
);

// About ClassicDataList
// delete a bunch of data in the datalist
// used like this eraseAbunchData( list,  front_pos,  final_pos)
//
ClassicLinkListFunctionStatues eraseAbunchData_inDataList(
	Classic_DataList* list,
	size_t														front_pos,
	size_t														final_pos
);


//----------------------------------------check_if_element_existed_functions----------------------------------------
// there are four functions in this sections
// 
// 1.check if the classiclinklist is empty
// fun1: isEmptyClassicLinkList
// 
// input :the checked list
// output: My defined bool(Sadly the org C doesn't define that)
// 
// ----------------------------------------------------------------------------------------------------------------
// 
// 2. check if the target elements is exsited in the datalist
// fun2: checkIsLocateinLinkList
// 
// input : the checked list ,the searched data and the Compared functions
// output: the locations that we first found it
// 
// ----------------------------------------------------------------------------------------------------------------
// 
// 3. return out the first locations that we found of the target elements
// func3:checkIsLocateinLinkList
// 
// input : the checked list ,the searched data and the Compared functions
// output: My defined bool(Sadly the org C doesn't define that)
// 
// ----------------------------------------------------------------------------------------------------------------
// 
// Warning : this functions required the PSDA abstractions is opened so you can use Position_Stored_Dynamic_ArrayFordyarr*
// to get the position
// 
// 4. return out a bunch of data that was contained in Position_Stored_Dynamic_ArrayFordyarr
// fun4:returnAbunchLocationsinLinkList
// 
// input : the checked list , the Position_Stored_Dynamic_ArrayFordyarr*(required init first)
// output: the Position_Stored_Dynamic_ArrayFordyarr that stored the positions!
//
// ----------------------------------------------------------------------------------------------------------------



// About ClassicLinkList
// check if the LinkList is empty
//
Bool isEmptyClassicLinkList(Classic_DataList* list);

// About ClassicLinkList
// check if the target elements is exsited in the datalist
//
Bool checkIsLocateinLinkList(
	Classic_DataList* list,
	void* data,
	LocateFunc														user_func
);

// About ClassicLinkList
// return out the first locations that we found of the target elements
// can use in this way: size_t pos = returnOutDatabyposinLinkList( list, data, user_func)
size_t returnOutDatabyposinLinkList(
	Classic_DataList* list,
	void* data,
	LocateFunc												user_func
);

#if OPENUPPOSARR

// About ClassicLinkList
// return out a bunch of data that was contained in Position_Stored_Dynamic_ArrayFordyarr
// can use in this way: Position_Stored_Dynamic_ArrayFordyarr* somePos = 
// returnAbunchLocationsinLinkList( list,  posArr,  data,  user_func)
//
Position_Stored_Dynamic_ArrayFordyarr* returnAbunchLocationsinLinkList(
	Classic_DataList* list,
	Position_Stored_Dynamic_ArrayFordyarr* posArr,
	void* data,
	LocateFunc												user_func
);

#endif 

//---------------------------------------Do_Something_to_the_datalist_functions-----------------------------------------
// there are seven functions in this sections
// 
// 1. Classic Print functions
// func1: Print_All_Data_LinkList
// to print all the data in the user_defined linklist
// 
// input : list and the user print , and the decision whether enjoyed a better print
// output: the statues of normal ,can be used in check or just ignore!
// 
// --------------------------------------------------------------------------------------------------------------------
// 
// 2. Do some change to the specific data
// to make some change directly to an element
// 
// input : the list ,the targeted positions and the way how you want to operate the data itself
// output: the statues of normal ,can be used in check or just ignore!
// 
// --------------------------------------------------------------------------------------------------------------------
// 
// 3. Do some change to all the data in the classiclinklist
// to make some change directly to the whole elements
// 
// input : the list ,the way how you want to operate the data itself
// output: the statues of normal ,can be used in check or just ignore!
// 
// --------------------------------------------------------------------------------------------------------------------
// 
// 4. Do specific change to an interval pos in the classicLickList
// to make some change directly to the interval elements
// 
// input : the list ,the front_pos and the final_pos
// output: the statues of normal ,can be used in check or just ignore!
// 
// -------------------------------------------------------------------------------------------------------------------
// 
// 5. reverse ClassicLinkList
// to reverse up the classic LinkList
// 
// input : the ready_reversed data
// output: the statues of normal ,can be used in check or just ignore!
// 
// -------------------------------------------------------------------------------------------------------------------
// 
// 6. combine two linkList into one
// to combine the two classic linklist into one!
// 
// input : the two linklist
// output: the merged linklist Pointer
// 
// -------------------------------------------------------------------------------------------------------------------
// 
// 7. sort the elements in the classicLinkList under the user's constructions
// to sort the ClassicLinkList
// 
// input : the classicLinklist
// output: the statues of normal ,can be used in check or just ignore!
// 
// -------------------------------------------------------------------------------------------------------------------
//


// About ClassicLinkList
// to print the data
// use in this way: Print_All_Data_LinkList( list, user_print,  whether_better_print)
//
ClassicLinkListFunctionStatues Print_All_Data_LinkList(
	Classic_DataList* list,
	MyPrint												user_print,
	BetterPrintSwitch_for_ClassicLinkList				whether_better_print
);


// About ClassicLinkList
// to make some change to the specific data
// use in this way:doChangetoSpecificElementinLinkList( list,  pos , user_func)
//
ClassicLinkListFunctionStatues doChangetoSpecificElementinLinkList(
	Classic_DataList* list,
	size_t											pos,
	Do_Specific_Change								user_func
);

// About ClassicLinkList
// to make some change to the interval data
// use in this way:doChangetoTargetIntervalDatainLinkList(list , pos1,pos2, user_func)
//
ClassicLinkListFunctionStatues doChangetoTargetIntervalDatainLinkList(
	Classic_DataList* list,
	size_t													front_pos,
	size_t													final_pos,
	Do_Specific_Change										user_func
);

// About ClassicLinkList
// to make some change to the whole elements in the data
// use in this way:doChangetoAllDatainLinkList( list,  user_func)
//
ClassicLinkListFunctionStatues doChangetoAllDatainLinkList(
	Classic_DataList* list,
	Do_Specific_Change									user_func
);


// About ClassicLinkList
// to reverse up the classiclinklist
// use in this way:ReverseLinkList(list)
//
ClassicLinkListFunctionStatues ReverseLinkList(Classic_DataList* list);

// About ClassicLinkList
// to merge two linklist into the one
// use in this way:mergeLinkList(list_be_added, list_adder, whether_copied)
//
Classic_DataList* mergeLinkList(
	Classic_DataList* list_be_added,
	Classic_DataList* list_adder,
	size_t												whether_copied
);

// About ClassicLinkList
// sort the classicLinklist in the bobblesort
// use in this way:sortClassicLinkListinBubbleSort(Classic_DataList* list, CompareFunc user_func) 
//
ClassicLinkListFunctionStatues sortClassicLinkListinBubbleSort(
	Classic_DataList* list,
	CompareFunc																user_func
);

//----------------------------------------------------Basic_Erase--------------------------------------------------------
// 
// 1.Erase A LinkList
// used in just clear a linklist
// func1: clearAClassicLinkList
// 
// input : just a classiclinklist
// output: the statues of normal ,can be used in check or just ignore!
// 
// ----------------------------------------------------------------------------------------------------------------------

//About ClassicLinkList
// Erase a classicLinkList
// Use in this way clearAClassicLinkList( list)
//
ClassicLinkListFunctionStatues clearAClassicLinkList(Classic_DataList* list);