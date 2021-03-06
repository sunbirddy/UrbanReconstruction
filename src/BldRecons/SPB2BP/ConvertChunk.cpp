#include "StdAfx.h"
#include "ConvertChunk.h"
#include "ConvertGrid.h"

CConvertChunk::CConvertChunk( int index, int number, CConvertGrid * grid ) :
	m_vecPatchPointData( number ),
	m_iPointIndex( 0 ),
	m_pGrid( grid ),
	m_iIndex( index ),
	m_iX( index / grid->m_nSideNumber ),
	m_iY( index % grid->m_nSideNumber ),
	m_vPosition( grid->m_cBoundingBox.m_vMin + CVector3D( m_iX * grid->m_dbUnit[ 0 ], m_iY * grid->m_dbUnit[ 1 ], 0.0 ) )
{
}

CConvertChunk::~CConvertChunk(void)
{
}

void CConvertChunk::PushPoint( SPBPoint * p )
{
	m_vecPatchPointData[ m_iPointIndex ].type = ( PointType )p->type;
	m_vecPatchPointData[ m_iPointIndex ].v = CVector3D( p->pos[ 0 ], p->pos[ 1 ], p->pos[ 2 ] );
	m_vecPatchPointData[ m_iPointIndex ].n = CVector3D( p->n[ 0 ], p->n[ 1 ], p->n[ 2 ] );
	m_vecPatchPointData[ m_iPointIndex ].flatness = p->flatness;
	m_vecPatchPointData[ m_iPointIndex ].patch.base = p->patch;
	m_vecPatchPointData[ m_iPointIndex ].patch.num = 0;
	m_iPointIndex ++;
}

//////////////////////////////////////////////////////////////////////////
// auxiliary functions
//////////////////////////////////////////////////////////////////////////

int CConvertChunk::Index( int x, int y )
{
	return ( x * m_pGrid->m_nUnitNumber[ 1 ] + y );
}

int CConvertChunk::Index( const CVector3D & v )
{
	CVector3D diff = v - m_vPosition;
	int x = ( int )( diff[0] / m_pGrid->m_dbGridLength ) ;
	RegularizeX( x );
	int y = ( int )( diff[1] / m_pGrid->m_dbGridLength );
	RegularizeY( y );
	return Index( x, y );
}

void CConvertChunk::RegularizeX( int & x )
{
	if ( x < 0 )
		x = 0;
	if ( x >= m_pGrid->m_nUnitNumber[ 0 ] )
		x = m_pGrid->m_nUnitNumber[ 0 ] - 1;
}

void CConvertChunk::RegularizeY( int & y )
{
	if ( y < 0 )
		y = 0;
	if ( y >= m_pGrid->m_nUnitNumber[ 1 ] )
		y = m_pGrid->m_nUnitNumber[ 1 ] - 1;
}
