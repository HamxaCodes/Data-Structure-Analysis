#include "array.h"
#include "fatal.h"
#include <stdlib.h>
#include "fileio.h"

#define MinArraySize (10)

enum KindOfEntry{ Legitimate, Empty, Deleted };


struct ArrayEntry      // name Cell is given to it
{
	ElementType Element;
	Record Data;
	enum KindOfEntry Info;
};

typedef struct ArrayEntry Cell;

struct ArrayRecord                 // pointer Array is given to it
{
	int ArraySize;
	Cell *TheCells;
};

// function to allocate memory for array of required size and its cells 
Array
CreateArray( int ArraySize)
{
	Array A;
	int i;
	
	// Checking for the proper size
	if( ArraySize < MinArraySize )
    {
		Error( "Array size too small" );
		return NULL;
	}
	
	// Alllocating memory for array
	A = malloc( sizeof( struct ArrayRecord ) );
	
	// Checking for the memory for array
	if (A==NULL)
	{
		FatalError("Out of memory.");
	}
	
	// Assigning the size to Array
	A->ArraySize = ArraySize;
	
	// Allocating memory for the cells of the Array
	A->TheCells = malloc( sizeof( Cell ) * A->ArraySize );
	
	// Checking for memory for the Cells  
	if( A->TheCells == NULL )
	{
		FatalError( "Out of space." );	
	}
	
	// making Info of the cells Empty
	for( i = 0; i < A->ArraySize; i++ )
	{
	 	A->TheCells[ i ].Info = Empty;
	}
		 
	return A;			
}

// function to insert the data stored in record R to the array A at given index I
void
Insert( Array A, Record R, Index I)
{	
	if( A==NULL )
	{
		FatalError("Not enough memory");
	}
	else
	{
		A->TheCells[ I ].Data = R; 
		A->TheCells[ I ].Element = RetrieveID(R);
		A->TheCells[ I ].Info = Legitimate;
	}	
}

void
PrintData( Array A)
{
	int i;
		
	for( i=0; i < A->ArraySize; i++ )
	{
		printf("INDEX %d:\t",i);
		if ( A->TheCells[ i ].Info == Legitimate )
		{
			Record R = A->TheCells[i].Data;
			printf("ID = %d \t Name = %s \t City = %s \t Sevice = %s\n", 
			RetrieveID(R), RetrieveName(R), RetrieveCity(R),RetrieveService(R) );
		}
		else if ( A->TheCells[ i ].Info == Empty )
			printf("Empty\n");
		// printing deleted as the the entry at the cell is deleted
		else if ( A->TheCells[ i ].Info == Deleted )
			printf("Deleted\n");
	}
}


Position
Find( Array A, ElementType Element )
{
	int i;
	for ( i = 0; i < A->ArraySize; i++ )
	{
		if ( A->TheCells[ i ].Element == Element )
			return i;
	}
}
		
void 
Delete( Array A, ElementType Element )
{
	Position P = Find( A, Element );
	if ( A->TheCells[ P ].Info == Empty )
	{
		Error( "Element not found" );	// exit with error message
	}
	// else, we have found our required cell, simply change the info of the cell to deleted
	A->TheCells[ P ].Info = Deleted;
}	

void
DestroyArray( Array A )
{
	int i;
	for ( i = 0; i < A->ArraySize; i++)
	{
		if (A->TheCells[i].Info != Empty)
		{
			Record R = A->TheCells[i].Data;
			free( RetrieveName( R ) );
			free( RetrieveCity( R ) );
			free( RetrieveService( R ) );
			free(R);
		}
	}
	free(A->TheCells);
	free(A);
}		

	
