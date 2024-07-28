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
	ClassicLinkList_NORMAL=0,
	ClassicLinkList_ERROR_IN_MALLOCING_SPACE = 1,
	ClassicLinkList_NULL_INPUT = -1,
	ClassicLinkList_Invalid_Input=-2,
	ClassicLinkList_UnFind=-3,
	ClassicLinkList_Invalid_Free=-4,
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

Position_Stored_Dynamic_ArrayFordyarr* Init_A_Postion_Stored_Dynamic_ArrayFordyarr()
{
	Position_Stored_Dynamic_ArrayFordyarr* pro_usable_space = (Position_Stored_Dynamic_ArrayFordyarr*)malloc(sizeof(Position_Stored_Dynamic_ArrayFordyarr));
	if (!pro_usable_space)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	pro_usable_space->posSpace = NULL;
	pro_usable_space->pos_size = 0;
	return pro_usable_space;
}

//About Positions_Stored_Dynamic_Array
//this function is aimed to output a series of locations that is stored in the pos
////Use PSDA_dyarr_OPEN to have a better shown ,else use PSDA_dyarr_CLOSE

ClassicLinkListFunctionStatues Show_All_Locations_In_PSDAfor_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr*					posarr,
	BetterPrintfor_PosDyarr									Whether_Better_Print
)
{
	if (!posarr)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (Whether_Better_Print == PSDA_dyarr_OPEN)
		printf("\nPositions are shown! :\n");
	for (int i = 0; i < posarr->pos_size; i++)
		printf("%u ", posarr->posSpace[i]);
	if (Whether_Better_Print == PSDA_dyarr_OPEN)
		printf("\nFinish Printing!\n");
	return ClassicLinkList_NORMAL;
}

//About Positions_Stored_Dynamic_Array
ClassicLinkListFunctionStatues Push_back_a_locations_in_PSDA_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr*					posarr, 
	int														pos_acquired
)
{
	int* pro_usable_space = (int*)realloc(posarr->posSpace, sizeof(int) * (posarr->pos_size + 1));
	if (!pro_usable_space)
	{
		SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
		exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
	}
	posarr->posSpace = pro_usable_space;
	posarr->posSpace[posarr->pos_size] = pos_acquired;
	posarr->pos_size++;
	return ClassicLinkList_NORMAL;
}
//About Positions_Stored_Dynamic_Array
//this function is aimed to return the number of locations
//Use PSDA_dyarr_OPEN to have a better shown ,else use PSDA_dyarr_CLOSE
size_t Get_pos_size_From_PSDA_for_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr*					posarr, 
	BetterPrintfor_PosDyarr									Whether_Shown_Print
)
{
	if (!posarr)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (Whether_Shown_Print == PSDA_dyarr_OPEN)
		printf("\nCurrent targeted data's total num is:%u!\n", posarr->pos_size);
	return posarr->pos_size;
}

//About Positions_Stored_Dynamic_Array
//return a pos that is targeted!
//
void* getPosbyPosinPSDA(
	Position_Stored_Dynamic_ArrayFordyarr* getter,
	size_t												pos
)
{
	if (!getter) 
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (pos > getter->pos_size)
	{
		SHOW_ERROR_ClassicLinkList_Invalid_Input;
		exit(ClassicLinkList_Invalid_Input);
	}
	for (int i = 0; i < pos; i++)
		return (char*)getter->posSpace + i * sizeof(size_t);
}

//About Positions_Stored_Dynamic_Array
ClassicLinkListFunctionStatues DesTroy_A_PSDA_for_dyarr(
	Position_Stored_Dynamic_ArrayFordyarr*					pointer_to_wishedfreeposarr
)
{
	if (!pointer_to_wishedfreeposarr)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	free(pointer_to_wishedfreeposarr->posSpace);
	free(pointer_to_wishedfreeposarr);
	pointer_to_wishedfreeposarr = NULL;
	return ClassicLinkList_NORMAL;
}
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


Classic_DataList* Init_A_ClassicLinkList()
{
	// create empty space
	Classic_DataList* pro_usable_space = (Classic_DataList*)malloc(sizeof(Classic_DataList));

	// Check whether init succeeded
	if (!pro_usable_space)
	{
		SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
		exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
	}

	// Default set 
	pro_usable_space->Head = NULL;
	pro_usable_space->current_size = 0;

	// return out the Structure
	return pro_usable_space;
}

// About ClassicLinkList
// to copy an already exited linklist
// Classic_DataList* List = Init_A_ClassicLinkList_By_CopyAClassicLinkList(Classic_DataList* list) 
//
Classic_DataList* Init_A_ClassicLinkList_By_CopyAClassicLinkList(
	Classic_DataList*										list
) 
{
	//check whether the input is legal
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	//check whether there is neccessity to copy 
	if (list->current_size == 0)
	{
		printf("No need to copy! it hasn't been initialize yet!");
		//Used to return NULL , but it is dangerous that two pointers points one things 
		return NULL;
	}

	//New a List and new a head and new the data of the head
	Classic_DataList* p_NewList = (Classic_DataList*)malloc(sizeof(Classic_DataList));
	Classic_DataNode* newHead = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));
	void* newdata = malloc(sizeof(list->Head->data));

	//check whether we init the node successfully
	if (newHead == NULL)
	{
		SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
		exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
	}

	if (newdata == NULL)
	{
		SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
		exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
	}

	//Do copy the data to the new head and finished initialization
	memcpy(newdata, list->Head->data, sizeof(list->Head->data));
	newHead->data = newdata;
	newHead->p_next_one = NULL;
	p_NewList->Head = newHead;
	p_NewList->current_size = 1;

	//Start copy other nodes
	Classic_DataNode* p_Currency = list->Head->p_next_one;
	Classic_DataNode* pCurCopy = p_NewList->Head;
	for (int i = 0; i < list->current_size-1; i++) 
	{
		//Copy the I-th node
		Classic_DataNode* newDataNode = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));

		//check if the initialization is illegal
		if(newDataNode==NULL)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}

		// prepare to copy data from the current node
		void* newdata = malloc(sizeof(p_Currency->data));

		// check if the initialization is illegal
		if (newdata == NULL)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}

		//copy the detailed node
		memcpy(newdata, p_Currency->data, sizeof(p_Currency->data));
		newDataNode->data = newdata;
		newDataNode->p_next_one = NULL;

		//Moving the pointer and prepared next copy
		pCurCopy->p_next_one = newDataNode;
		pCurCopy = pCurCopy->p_next_one;
		p_Currency = p_Currency->p_next_one;
	}

	//Data copy finished , init the cur_size
	p_NewList->current_size = list->current_size;
	return p_NewList;
}

// About ClassicLinkList
// to updata a static array into a ClassicLinkList
// Classic_DataList* List = UpdateStaticArray2ClassicLinkList(
// void* inputArray, 
// size_t dataSize, 
// size_t dataNum
// )
//
Classic_DataList* UpdateStaticArray2ClassicLinkList(
	void*									inputArray, 
	size_t									dataSize, 
	size_t									dataNum
)
{
	if (inputArray == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	Classic_DataList* pro_usable_space = (Classic_DataList*)malloc(sizeof(Classic_DataList));
	Classic_DataNode* FirstHeaddata = (Classic_DataNode*)malloc(sizeof(Classic_DataNode*));
	void* datapiece = malloc(dataSize);
	if (
		pro_usable_space == NULL
		&&
		FirstHeaddata == NULL
		&&
		datapiece == NULL
		)
	{
		SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
		exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
	}
	memcpy(datapiece, inputArray, dataSize);
	FirstHeaddata->data = datapiece;
	FirstHeaddata->p_next_one = NULL;
	pro_usable_space->current_size = 1;
	pro_usable_space->Head = FirstHeaddata;
	for (int i = 1; i < dataNum; i++)
	{
		Classic_DataNode* p_Currency = pro_usable_space->Head;
		while (p_Currency->p_next_one)
		{
			p_Currency = p_Currency->p_next_one;
		}
		void* datastored = malloc(dataSize);
		if (!datastored)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}
		memcpy(datastored, (char*)inputArray + i * dataSize, dataSize);
		Classic_DataNode* datanode = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));
		if (!datanode)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}
		datanode->data = datastored;
		datanode->p_next_one = NULL;
		p_Currency->p_next_one = datanode;
		pro_usable_space->current_size++;
	}
	return pro_usable_space;
}

//----------------------------------------Basic_Add_Functions------------------------
// there are four basic input functions:
// 
// ----------------------------------------------------------------------------------
// 1. push back an element into the classicLinkList
// func1 : ClassicLinkListFunctionStatues Push_Back_Into_A_ClassicLinkList
//
// input : the inserted list ,the data wanted to be inserted and the inserted datasize
// output: the statues of normal ,can be used in check or just ignore!
// 
// ----------------------------------------------------------------------------------
// 2. insert back an element into the classicLinkList by offering a valid pos
// func2 : ClassicLinkListFunctionStatues Insert_into_AClassicLinkList
// 
// 
// input : the inserted list , the data ,the datasize as well as the position you wanted to insert
// output: the statues of normal ,can be used in check or just ignore!
// 
// ----------------------------------------------------------------------------------
// 
// 3. push back a bunch of data into the classicLinkList like the first function
// func3 :ClassicLinkListFunctionStatues push_Back_BunchDataintoClassicLinkList
// 
// input : the inserted list , the data ,the datasize as well as the position you wanted to insert
// output: the statues of normal ,can be used in check or just ignore!
// 
// ----------------------------------------------------------------------------------
// 4. insert back a bunch of data into the classicLinkList like the second function
// func4: ClassicLinkListFunctionStatues Insert_A_Bunch_of_data_intoClassicLinkList
//
// input : the inserted list , the static array ,the datasize in the static array as well as the position you wanted to insert
// output: the statues of normal ,can be used in check or just ignore! 
// 
//----------------------------------------Basic_Add_Functions-------------------------

// About ClassicLinkList
// push back some data ,like dynamic array , into the final position
//Used like this Push_Back_Into_A_ClassicLinkList(appendedClassicLinkList, data ,sizeof(data))
//
ClassicLinkListFunctionStatues Push_Back_Into_A_ClassicLinkList(
	Classic_DataList*											list, 
	void*														data,
	size_t														datasize
)
{
	if (!list)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (!data)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	Classic_DataNode* p_Currency = list->Head;
	if(list->Head != NULL)
	{
		while (p_Currency->p_next_one)
		{
			p_Currency = p_Currency->p_next_one;
		}
		void* datastored = malloc(datasize);
		if (!datastored)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}
		memcpy(datastored, data, datasize);
		Classic_DataNode* datanode = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));
		if (!datanode)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}
		datanode->data = datastored;
		datanode->p_next_one = NULL;
		p_Currency->p_next_one = datanode;
		list->current_size++;
	}
	else
	{
		void* datastored = malloc(datasize);
		if (!datastored)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}
		memcpy(datastored, data, datasize);
		Classic_DataNode* datanode = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));
		if (!datanode)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}
		datanode->data = datastored;
		datanode->p_next_one = NULL;
		list->Head = datanode;
		list->current_size++;
	}
	return ClassicLinkList_NORMAL;
}

// About ClassicDataList
// insert back a data into the datalist
// used like this: Insert_into_AClassicLinkList(inserted list, input data,dataSize,insertion_pos)
// 
ClassicLinkListFunctionStatues Insert_into_AClassicLinkList(
	Classic_DataList*										list, 
	void*													data,
	size_t													dataSize,
	size_t													pos
)
{
	
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (data == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (pos<0 || pos>list->current_size)
	{
		SHOW_ERROR_ClassicLinkList_Invalid_Input;
		exit(ClassicLinkList_Invalid_Input);
	}
	if (pos == 0)
	{
		Classic_DataNode* stored = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));
		if (stored == NULL)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}
		void* dataPiece = malloc(dataSize);
		memcpy(dataPiece, data, dataSize);
		stored->data = dataPiece;
		stored->p_next_one = list->Head;
		list->Head = stored;
		list->current_size++;
		return ClassicLinkList_NORMAL;
	}
	Classic_DataNode* pCurrency = list->Head;
	Classic_DataNode* stored = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));
	if (stored == NULL)
	{
		SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
		exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
	}
	void* dataPiece = malloc(dataSize);
	memcpy(dataPiece, data, dataSize);
	stored->data = dataPiece;
	for (int i = 0; i < pos; i++)
	{
		pCurrency = pCurrency->p_next_one;
	}
	stored->p_next_one = pCurrency->p_next_one;
	pCurrency->p_next_one = stored;
	list->current_size++;
	return ClassicLinkList_NORMAL;
}

// About ClassicDataList
// push back a bunch data into the datalist
// used like this : push_Back_BunchDataintoClassicLinkList( inserted_list , the static array ,the elementsize ,the element num)
//
ClassicLinkListFunctionStatues push_Back_BunchDataintoClassicLinkList(
	Classic_DataList*										list,
	void*													inputArray, 
	size_t													sigElemSize, 
	size_t													arrayNum
)
{
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}

	if(inputArray==NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}


	//Equally as to updata a Static Array into a ClassicLinkList
	//Once just use  UpdateStaticArray2ClassicLinkList(),but i'm afraid of unable to use this functions
	//as it is said: "DO NOT motivate another functions , try to finish all work if neccessary"
	if (list->Head == NULL)
	{
		//New a List and new a head and new the data of the head
		Classic_DataList* p_NewList = (Classic_DataList*)malloc(sizeof(Classic_DataList));
		Classic_DataNode* newHead = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));
		void* newdata = malloc(sizeof(list->Head->data));

		//check whether we init the node successfully
		if (newHead == NULL)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}

		if (newdata == NULL)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}

		//Do copy the data to the new head and finished initialization
		memcpy(newdata, list->Head->data, sizeof(list->Head->data));
		newHead->data = newdata;
		newHead->p_next_one = NULL;
		p_NewList->Head = newHead;
		p_NewList->current_size = 1;

		//Start copy other nodes
		Classic_DataNode* p_Currency = list->Head->p_next_one;
		Classic_DataNode* pCurCopy = p_NewList->Head;
		for (int i = 0; i < list->current_size - 1; i++)
		{
			//Copy the I-th node
			Classic_DataNode* newDataNode = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));

			//check if the initialization is illegal
			if (newDataNode == NULL)
			{
				SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
				exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
			}

			// prepare to copy data from the current node
			void* newdata = malloc(sizeof(p_Currency->data));

			// check if the initialization is illegal
			if (newdata == NULL)
			{
				SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
				exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
			}

			//copy the detailed node
			memcpy(newdata, p_Currency->data, sizeof(p_Currency->data));
			newDataNode->data = newdata;
			newDataNode->p_next_one = NULL;

			//Moving the pointer and prepared next copy
			pCurCopy->p_next_one = newDataNode;
			pCurCopy = pCurCopy->p_next_one;
			p_Currency = p_Currency->p_next_one;
		}

		//Data copy finished , init the cur_size
		p_NewList->current_size = list->current_size;
		list = p_NewList;
		return ClassicLinkList_NORMAL;
	}

	//for this section , that means the head isn't NULL , just copy as usual:
	Classic_DataNode* pCur = list->Head;
	for (int i = 0; i < list->current_size-1; i++) 
	{
		pCur = pCur->p_next_one;
	}
	
	for (int i = 0; i < arrayNum; i++) 
	{
		Classic_DataNode* pCopyCur = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));
		void* copyData = malloc(sizeof(sigElemSize));
		if (pCopyCur == NULL && copyData == NULL) 
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}

		memcpy(copyData, (char*)inputArray + i * sigElemSize, sigElemSize);
		pCopyCur->data = copyData;
		pCopyCur->p_next_one = NULL;
		pCur->p_next_one = pCopyCur;
		pCur = pCur->p_next_one;
	}

	list->current_size += arrayNum;
	return ClassicLinkList_NORMAL;
}

// About ClassicDataList
// insert back a bunch of data into the datalist
// used like this: Insert_into_AClassicLinkList(inserted list, insertion_pos,input array ,Single dataSize, the amount of elements)
// 
ClassicLinkListFunctionStatues Insert_A_Bunch_of_data_intoClassicLinkList(
	Classic_DataList*								list,
	size_t											pos,
	void*											inputArray,
	size_t											sigElemSize,
	size_t											arrayNum
) 
{
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (inputArray == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}

	if (pos > list->current_size)
	{
		SHOW_WARNING_ClassicLinkList_OVERLAP_POS;
		SHOW_WHETHER_ACCCEPTED("y/n: y for yes , n for n");
		int choice;
		scanf("%c", &choice);
		if (choice == 'y')
		{
			pos = list->current_size;
		}
		else
		{
			SHOW_ERROR_ClassicLinkList_Invalid_Input;
			exit(ClassicLinkList_Invalid_Input);
		}
	}

	Classic_DataNode* pCurNow = NULL;
	Classic_DataNode* pStart = NULL;

	for(int i = 0 ; i < arrayNum ; i++)
	{

		Classic_DataNode* pCopyCur = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));
		void* copydata = malloc(sigElemSize);

		if (pCopyCur == NULL && copydata == NULL)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}

		memcpy(copydata, (char*)inputArray + i * sigElemSize, sigElemSize);
		pCopyCur->data = copydata;
		pCopyCur->p_next_one = NULL;

		if (i == 0)
		{
			pCurNow = pCopyCur;
			pStart = pCopyCur;
			continue;
		}
		pCurNow->p_next_one = pCopyCur;
		pCurNow = pCurNow->p_next_one;
	}
	
	if (pos == 0)
	{
		pCurNow->p_next_one = list->Head;
		list->Head = pStart;
		list->current_size += arrayNum;
		return ClassicLinkList_NORMAL;
	}

	Classic_DataNode* pCur = list->Head;
	for (int i = 0; i < pos; i++) 
	{
		pCur = pCur->p_next_one;
	}

	pCurNow->p_next_one = pCur->p_next_one;
	pCur->p_next_one = pStart;
	list->current_size += arrayNum;
	return ClassicLinkList_NORMAL;
}

//------------------------------------------Deletion_Functions-------------
// there are two basic type of functions in the sections
// 1. Erase a targeted element and erase it from the ClassicDataList
// fun1:eraseAElementfromDataList
// 
// input : the list and the erase position
// output: the statues of normal ,can be used in check or just ignore!
// 
// --------------------------------------------------------------------------
// 
// 2.Erase some target elements from the ClassicDataList
// fun2:eraseAbunchData
// 
// input: the list and the start position as well as the last position, that means offer a paired pos
// output: the statues of normal ,can be used in check or just ignore!
//------------------------------------------Deletion_Functions----------------


// About ClassicDataList
// delete a  data in the datalist by offering a position
//used like this: eraseAElementfromDataList(list, erasing_pos)
//
ClassicLinkListFunctionStatues eraseAElementfromDataList(
	Classic_DataList*										list,
	size_t													pos
) 
{
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (pos<0 || pos>list->current_size)
	{
		SHOW_ERROR_ClassicLinkList_Invalid_Input;
		exit(ClassicLinkList_Invalid_Input);
	}
	if (pos == 0)
	{
		Classic_DataNode* pNewHead = list->Head->p_next_one;
		Classic_DataNode* pDel = list->Head;
		list->Head = pNewHead;
		free(pDel->data);
		list->current_size--;
		return ClassicLinkList_NORMAL;
	}
	Classic_DataNode* pCur = list->Head;
	for (int i = 0; i < pos-1; i++)
	{
		pCur = pCur->p_next_one;
	}
	Classic_DataNode* pDel = pCur->p_next_one;
	pCur->p_next_one = pDel->p_next_one;
	free(pDel->data);
	free(pDel);
	list->current_size--;
	return ClassicLinkList_NORMAL;
}


// About ClassicDataList
// delete a bunch of data in the datalist
// used like this eraseAbunchData( list,  front_pos,  final_pos)
//
ClassicLinkListFunctionStatues eraseAbunchData_inDataList(
	Classic_DataList*											list, 
	size_t														front_pos,
	size_t														final_pos
)
{
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (front_pos<0 || front_pos>list->current_size)
	{
		SHOW_ERROR_ClassicLinkList_Invalid_Input;
		exit(ClassicLinkList_Invalid_Input);
	}
	if (final_pos<0 || final_pos>list->current_size)
	{
		SHOW_ERROR_ClassicLinkList_Invalid_Input;
		exit(ClassicLinkList_Invalid_Input);
	}
	if (front_pos > final_pos)
	{
		SHOW_WARNING_ClassicLinkList_SWAPPED_POS;
		SHOW_WHETHER_ACCCEPTED("y/n: y for yes , n for n");
		int choice;
		scanf("%c", &choice);
		if (choice == 'y') 
		{
			int temp = final_pos;
			final_pos = front_pos;
			front_pos = temp;
		}
		else
		{
			SHOW_ERROR_ClassicLinkList_Invalid_Input;
			exit(ClassicLinkList_Invalid_Input);
		}
	}
	Bool flag =False;
	if (front_pos == 0) 
	{
		flag = True;
		front_pos++;
	}
	Classic_DataNode* pCur = list->Head;
	for (int i = 0; i < front_pos-1; i++) 
	{
		pCur = pCur->p_next_one;
	}
	int cur_place = front_pos-1;
	while (cur_place <= final_pos-1) {
		Classic_DataNode* pDel = pCur->p_next_one;
		pCur->p_next_one = pDel->p_next_one;
		free(pDel);
		cur_place++;
	}
	list->current_size -= final_pos - front_pos +1;
	if (flag == True) {
		Classic_DataNode* pNewHead = pCur->p_next_one;
		Classic_DataNode* pDel = list->Head;
		list->Head = pNewHead;
		free(pDel->data);
		front_pos++;
		list->current_size--;
	}
	return ClassicLinkList_NORMAL;
}

//----------------------------------------check_if_element_existed_functions-----
// there are four functions in this sections
// 
// 1.check if the classiclinklist is empty
// fun1: isEmptyClassicLinkList
// 
// input :the checked list
// output: My defined bool(Sadly the org C doesn't define that)
// 
// ------------------------------------------------------------------------------
// 
// 2. check if the target elements is exsited in the datalist
// fun2: checkIsLocateinLinkList
// 
// input : the checked list ,the searched data and the Compared functions
// output: the locations that we first found it
// 
// -------------------------------------------------------------------------------
// 
// 3. return out the first locations that we found of the target elements
// func3:checkIsLocateinLinkList
// 
// input : the checked list ,the searched data and the Compared functions
// output: My defined bool(Sadly the org C doesn't define that)
// 
// --------------------------------------------------------------------------------
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
// ---------------------------------------------------------------------------------



// About ClassicLinkList
// check if the LinkList is empty
//
Bool isEmptyClassicLinkList(Classic_DataList* list)
{
	if (list->current_size == 0)
	{
		return True;
	}
	return False;
}

// About ClassicLinkList
// check if the target elements is exsited in the datalist
//
Bool checkIsLocateinLinkList(
	Classic_DataList*												list, 
	void*															data,
	LocateFunc														user_func
)
{
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (data == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (user_func == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	Classic_DataNode* pCur = list->Head;
	for (int i = 0; i < list->current_size; i++)
	{
		if (user_func(data, pCur->data)) {
			return True;
		}
	}
	return False;
}

// About ClassicLinkList
// return out the first locations that we found of the target elements
// can use in this way: size_t pos = returnOutDatabyposinLinkList( list, data, user_func)
size_t returnOutDatabyposinLinkList(
	Classic_DataList*										list, 
	void*													data, 
	LocateFunc												user_func
)
{
	Classic_DataNode* pCur = list->Head;
	for (int i = 0; i < list->current_size; i++)
	{
		if (user_func(data, pCur->data)) {
			return i;
		}
		pCur = pCur->p_next_one;
	}
	return Unfind_ClassicLinkList;
}


// Make sure the OPENUPPOSARR == 1 if wanted to use it

#if OPENUPPOSARR

// About ClassicLinkList
// return out a bunch of data that was contained in Position_Stored_Dynamic_ArrayFordyarr
// can use in this way: Position_Stored_Dynamic_ArrayFordyarr* somePos = 
// returnAbunchLocationsinLinkList( list,  posArr,  data,  user_func)
//
Position_Stored_Dynamic_ArrayFordyarr* returnAbunchLocationsinLinkList(
	Classic_DataList*										list, 
	Position_Stored_Dynamic_ArrayFordyarr*					posArr, 
	void*													data,
	LocateFunc												user_func
)
{
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (data == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (posArr == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	Classic_DataNode* p_Currency = list->Head;
	int possible_count = 0;
	for (int i = 0; i < list->current_size; i++)
	{
		if ((*user_func)(data, p_Currency->data))
		{
			int* pro_usable_stored_space = (int*)realloc(posArr->posSpace, sizeof(int) * (possible_count + 1));
			if (!pro_usable_stored_space)
			{
				SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
				exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
			}
			posArr->posSpace = pro_usable_stored_space;
			posArr->posSpace[possible_count] = i;
			possible_count++;
			posArr->pos_size = possible_count;
		}
		p_Currency = p_Currency->p_next_one;
	}
	if (posArr->pos_size)
		return posArr;
	return Unfind_ClassicLinkList;
}

#endif 




//---------------------------------------Do_Something_to_the_datalist_functions----------
// there are seven functions in this sections
// 
// 1. Classic Print functions
// func1: Print_All_Data_LinkList
// to print all the data in the user_defined linklist
// 
// input : list and the user print , and the decision whether enjoyed a better print
// output: the statues of normal ,can be used in check or just ignore!
// 
// ------------------------------------------------------------------------------------
// 
// 2. Do some change to the specific data
// to make some change directly to an element
// 
// input : the list ,the targeted positions and the way how you want to operate the data itself
// output: the statues of normal ,can be used in check or just ignore!
// 
// ------------------------------------------------------------------------------------
// 
// 3. Do some change to all the data in the classiclinklist
// to make some change directly to the whole elements
// 
// input : the list ,the way how you want to operate the data itself
// output: the statues of normal ,can be used in check or just ignore!
// 
// -----------------------------------------------------------------------------------
// 
// 4. Do specific change to an interval pos in the classicLickList
// to make some change directly to the interval elements
// 
// input : the list ,the front_pos and the final_pos
// output: the statues of normal ,can be used in check or just ignore!
// 
// -----------------------------------------------------------------------------------
// 
// 5. reverse ClassicLinkList
// to reverse up the classic LinkList
// 
// input : the ready_reversed data
// output: the statues of normal ,can be used in check or just ignore!
// 
// -----------------------------------------------------------------------------------
// 
// 6. combine two linkList into one
// to combine the two classic linklist into one!
// 
// input : the two linklist
// output: the merged linklist Pointer
// 
// -----------------------------------------------------------------------------------
// 
// 7. sort the elements in the classicLinkList under the user's constructions
// to sort the ClassicLinkList
// 
// input : the classicLinklist
// output: the statues of normal ,can be used in check or just ignore!
// 
// ---------------------------------------------------------------------------------


// About ClassicLinkList
// to print the data
// use in this way: Print_All_Data_LinkList( list, user_print,  whether_better_print)
//
ClassicLinkListFunctionStatues Print_All_Data_LinkList(
	Classic_DataList*									list,
	MyPrint												user_print, 
	BetterPrintSwitch_for_ClassicLinkList				whether_better_print
)
{

	if (!list)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}

	if (!user_print)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}

	if (whether_better_print == ClassicLinkList_OPEN) {
		printf("\nStart printing:\n");
	}


	Classic_DataNode* p_Currency = list->Head;

	for (int i = 0; i < list->current_size; i++)
	{
		user_print(p_Currency->data);
		p_Currency = p_Currency->p_next_one;
	}


	if (whether_better_print == ClassicLinkList_OPEN) {
		printf("\nFinish printing:\n");
	}

	return ClassicLinkList_NORMAL;
}

// About ClassicLinkList
// to make some change to the specific data
// use in this way:doChangetoSpecificElementinLinkList( list,  pos , user_func)
//
ClassicLinkListFunctionStatues doChangetoSpecificElementinLinkList(
	Classic_DataList*								list, 
	size_t											pos ,
	Do_Specific_Change								user_func
) 
{
	if (list == NULL&&user_func==NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (pos<0 || pos>list->current_size)
	{
		SHOW_ERROR_ClassicLinkList_Invalid_Input;
		exit(ClassicLinkList_Invalid_Input);
	}
	Classic_DataNode* pCur = list->Head;
	for (int i = 0; i < pos; i++)
	{
		pCur = pCur->p_next_one;
	}
	user_func(pCur->data);
	return ClassicLinkList_NORMAL;
}

// About ClassicLinkList
// to make some change to the interval data
// use in this way:doChangetoTargetIntervalDatainLinkList(list , pos1,pos2, user_func)
//
ClassicLinkListFunctionStatues doChangetoTargetIntervalDatainLinkList(
	Classic_DataList*										list, 
	size_t													front_pos,
	size_t													final_pos,
	Do_Specific_Change										user_func
) 
{
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (front_pos<0 || front_pos>list->current_size)
	{
		SHOW_ERROR_ClassicLinkList_Invalid_Input;
		exit(ClassicLinkList_Invalid_Input);
	}
	if (final_pos<0 || final_pos>list->current_size)
	{
		SHOW_ERROR_ClassicLinkList_Invalid_Input;
		exit(ClassicLinkList_Invalid_Input);
	}
	if (front_pos > final_pos)
	{
		SHOW_WARNING_ClassicLinkList_SWAPPED_POS;
		SHOW_WHETHER_ACCCEPTED("y/n: y for yes , n for n");
		int choice;
		scanf("%c", &choice);
		if (choice == 'y')
		{
			int temp = final_pos;
			final_pos = front_pos;
			front_pos = temp;
		}
		else
		{
			SHOW_ERROR_ClassicLinkList_Invalid_Input;
			exit(ClassicLinkList_Invalid_Input);
		}
	}

	Classic_DataNode* pCur = list->Head;
	for (int i = 0; i < front_pos; i++) {
		pCur = pCur->p_next_one;
	}
	for (int i = front_pos; i < final_pos+1; i++)
	{
		user_func(pCur->data);
		pCur = pCur->p_next_one;
	}
	return ClassicLinkList_NORMAL;

}

// About ClassicLinkList
// to make some change to the whole elements in the data
// use in this way:doChangetoAllDatainLinkList( list,  user_func)
//
ClassicLinkListFunctionStatues doChangetoAllDatainLinkList(
	Classic_DataList*									list,
	Do_Specific_Change									user_func
)
{
	if (list == NULL && user_func == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	Classic_DataNode* pCur = list->Head;
	for (int i = 0; i < list->current_size; i++) 
	{
		user_func(pCur->data);
		pCur=pCur->p_next_one;
	}
	return ClassicLinkList_NORMAL;
}

// About ClassicLinkList
// to reverse up the classiclinklist
// use in this way:ReverseLinkList(list)
//
ClassicLinkListFunctionStatues ReverseLinkList(Classic_DataList* list)
{
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (list->current_size == 1)
	{
		printf("No need in reversing!,try a longer one lol");
		return ClassicLinkList_NORMAL;
	}
	if (list->current_size == 2)
	{
		Classic_DataNode* headFisrt = list->Head;
		Classic_DataNode* pFin = headFisrt->p_next_one;
		pFin->p_next_one = headFisrt;
		headFisrt->p_next_one = NULL;
		list->Head = pFin;
		return ClassicLinkList_NORMAL;
	}
	Classic_DataNode* pFinal = list->Head->p_next_one;
	Classic_DataNode* pPrior = list->Head;
	while (pFinal!= NULL) 
	{
		Classic_DataNode* tempFin = pFinal->p_next_one;
		pFinal->p_next_one = pPrior;
		pPrior = pFinal;
		pFinal = tempFin;
	}
	list->Head = pPrior;
}

// About ClassicLinkList
// to merge two linklist into the one
// use in this way:mergeLinkList(list_be_added, list_adder, whether_copied)
//
Classic_DataList* mergeLinkList(
	Classic_DataList*									list_be_added, 
	Classic_DataList*									list_adder, 
	size_t												whether_copied
)
{
	if (list_be_added == NULL && list_adder == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	Classic_DataNode* pCur=list_be_added->Head;
	for (int i = 0; i < list_be_added->current_size-1; i++)
	{
		pCur = pCur->p_next_one;
	}
	//Do not copy , instead just merge!
	if (whether_copied==ClassicLinkList_NO_COPY) {
		pCur->p_next_one = list_adder->Head;
		list_be_added->current_size += list_adder->current_size;
		return list_be_added;
	}
	Classic_DataNode* pAdder = list_adder->Head;
	for (int i = 0; i < list_adder->current_size; i++)
	{
		//prepare the space
		Classic_DataNode* pCopy = (Classic_DataNode*)malloc(sizeof(Classic_DataNode));
		void* dataCopy = malloc(sizeof(pAdder->data));
		if (pCopy == NULL && dataCopy == NULL)
		{
			SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
			exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
		}
		//Using to copy data and initialize the copied node
		memcpy(dataCopy, pAdder->data, sizeof(pAdder->data));
		pCopy->data = dataCopy;
		pCopy->p_next_one = NULL;
		//then push back into the linklist
		pCur->p_next_one = pCopy;
		//Moving the copy pointer
		pAdder = pAdder->p_next_one;
		pCur = pCur->p_next_one;
	}
	list_be_added->current_size += list_adder->current_size;
	return list_be_added;
}

// About ClassicLinkList
// sort the classicLinklist in the bobblesort
// use in this way:sortClassicLinkListinBubbleSort(Classic_DataList* list, CompareFunc user_func) 
//
ClassicLinkListFunctionStatues sortClassicLinkListinBubbleSort(
	Classic_DataList*														list, 
	CompareFunc																user_func
) 
{
	if (list == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	if (user_func == NULL)
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}
	for (int i = 0; i < list->current_size-1; i++)
	{
		Classic_DataNode* pCur = list->Head;
		for(int j=0;j<list->current_size-i-1;j++)
		{
			//this two for loops are just standard BobbleSort
			if (user_func(pCur->data, pCur->p_next_one->data))
			{
				void* tempdata = malloc(sizeof(pCur->data));
				memcpy(tempdata, pCur->data, sizeof(pCur->data));
				int tempdatasize = sizeof(pCur->data);
				//Before Swap,make sure that the dataContainer is huge enough to contain a new space
				if (sizeof(pCur->p_next_one->data) > sizeof(pCur->data))
				{
					void* pTempSwap = realloc(pCur->data, sizeof(pCur->p_next_one->data));
					if (pTempSwap == NULL)
					{
						SHOW_ERROR_ClassicLinkList_ERROR_IN_MALLOCING_SPACE;
						exit(ClassicLinkList_ERROR_IN_MALLOCING_SPACE);
					}
					pCur->data = pTempSwap;
				}
				//Copy and swap
				memcpy(pCur->data, pCur->p_next_one->data, sizeof(pCur->p_next_one->data));
				memcpy(pCur->p_next_one->data, tempdata, tempdatasize);
			}
			//Moving pointer to the next one
			pCur = pCur->p_next_one;
		}
	}
	return ClassicLinkList_NORMAL;
}

//----------------------------------------------------Basic_Erase------------------------------
// 
// 1.Erase A LinkList
// used in just clear a linklist
// func1: clearAClassicLinkList
// 
// input : just a classiclinklist
// output: the statues of normal ,can be used in check or just ignore!
// 
// --------------------------------------------------------------------------------------------

//About ClassicLinkList
// Erase a classicLinkList
// Use in this way clearAClassicLinkList( list)
//
ClassicLinkListFunctionStatues clearAClassicLinkList(Classic_DataList* list)
{
	if (list == NULL) 
	{
		SHOW_ERROR_ClassicLinkList_NULL_INPUT;
		exit(ClassicLinkList_NULL_INPUT);
	}

	Classic_DataNode* pCur = list->Head->p_next_one;
	Classic_DataNode* pDel = list->Head;
	if (list->current_size == 1) {
		free(pDel);
	}
	for (int i = 0; i < list->current_size-1; i++)
	{
		free(pDel);
		pDel = pCur;
		pCur = pCur->p_next_one;
	}

	list->current_size = 0 ;
	return ClassicLinkList_NORMAL;
}