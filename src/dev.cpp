/***************************************************************************
                          dev.cpp  -  description
                             -------------------
    begin                : Wed Aug 1 2001
    copyright            : (C) 2001, 2002 by Roland Riegel
    email                : feedback@roland-riegel.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dev.h"

Dev::Dev() : Proc::Proc()
{
	
	for( int i = 0; i < 2; i++ )
	{
		
		device_status[i] = new Status();
		traffic_graph[i] = new Graph();
		
		switch(i)
		{
			case 0:
				traffic_graph[i] -> setTrafficWithMaxDeflectionOfBars( STANDARD_BAR_MAX_IN );
				break;
			case 1:
				traffic_graph[i] -> setTrafficWithMaxDeflectionOfBars( STANDARD_BAR_MAX_OUT );
				break;
		}
		
		device_status[i] -> setAverageSmoothness( STANDARD_AVERAGE_SMOOTHNESS );
		
	}
	
	setShowGraphs( STANDARD_SHOW_GRAPHS );
	
	setProcDev( STANDARD_NETWORK_DEVICE );
	
	setStatusFormat( STANDARD_TRAFFIC_FORMAT, STANDARD_DATA_FORMAT );
	
	setDeviceNumber(0);
	setTotalNumberOfDevices(0);
	
}

Dev::~Dev()
{
}

//update the device's data
void Dev::update()
{
	//read current traffic
	float *currentio = readLoad();
	
	//calculate the traffic (Bytes/s)
	currentio[0] = currentio[0] / ( getElapsedTime() / 1000 );
	currentio[1] = currentio[1] / ( getElapsedTime() / 1000 );
	
	//update graphs and statistics
	for( int i = 0; i < 2; i++ )
	{
		if( ProcDevExists() )
		{
			device_status[i] -> update( (int) currentio[i], (unsigned int) ( i == 0 ? totalIn() : totalOut() ) );
			traffic_graph[i] -> update( (int) currentio[i] );
		}
		else
		{
			device_status[i] -> resetTrafficData();
			traffic_graph[i] -> resetTrafficData();
		}
	}
}

//print the device's data
void Dev::print( Window& window )
{
	char fText[100] = "";
	
	//if device does not exist
	if ( ! ProcDevExists() )
	{
		//... print warning message ...
		sprintf( fText, "Device %s (%i/%i): does not exist\n", ProcDev(), m_devicenumber, m_totalnumberofdevices );
		window.print( fText );
		for( int i = 0; i < window.width(); i++ )
			window.print( '=' );
		window.print( '\n' );
		
		//... and exit
		return;
	}
	
	//print header
	sprintf( fText, "Device %s (%i/%i):\n", ProcDev(), m_devicenumber, m_totalnumberofdevices );
	window.print( fText );
	for( int i = 0; i < window.width(); i++ )
		window.print( '=' );
	
	//if graphs should be shown ...
	if( m_showgraphs )
	{
		//incoming traffic
		window.print( "Incoming:\n" );
		
		traffic_graph[0] -> setNumOfBars( window.width() * 2 / 3 );
		traffic_graph[0] -> setHeightOfBars( ( window.height() - window.y() - 1 ) / 2 );
		traffic_graph[0] -> print( window, 0, window.y() );
		
		device_status[0] -> print( window, window.width() * 2 / 3 + 2, window.y() - 5, m_trafficformat, m_dataformat );
		
		//outgoing traffic
		window.print( "Outgoing:\n" );
		
		traffic_graph[1] -> setNumOfBars( window.width() * 2 / 3 );
		traffic_graph[1] -> setHeightOfBars( window.height() - window.y() );
		traffic_graph[1] -> print( window, 0, window.y() );
		
		device_status[1] -> print( window, window.width() * 2 / 3 + 2, window.y() - 4, m_trafficformat, m_dataformat );
	}
	//... or not
	else
	{
		window.print( "Incoming:" );
		window.setX( window.width() / 2 );
		window.print( "Outgoing:\n" );
		
		device_status[0] -> print( window, 0, window.y(), m_trafficformat, m_dataformat ); //incoming traffic
		device_status[1] -> print( window, window.width() / 2, window.y(), m_trafficformat, m_dataformat ); //outgoing traffic
		
		window.print( '\n' );
	}
}

//sets if the graphs should be shown or not
void Dev::setShowGraphs( bool new_showgraphs )
{
	m_showgraphs = new_showgraphs;
}

//set the in- and outcoming graphs' averagesmoothness
void Dev::setAverageSmoothness( int new_averagesmoothness )
{
	for( int i = 0; i < 2; i++ )
		device_status[i] -> setAverageSmoothness( new_averagesmoothness );
}

//set the graphs' max deflection (max traffic level)
void Dev::setTrafficWithMaxDeflectionOfGraphs( int new_trafficinwithmaxdeflectionofgraphs, int new_trafficoutwithmaxdeflectionofgraphs  )
{
	
	for( int i = 0; i < 2; i++ )
		switch(i)
		{
			case 0:
				traffic_graph[i] -> setTrafficWithMaxDeflectionOfBars( new_trafficinwithmaxdeflectionofgraphs );
				break;
			case 1:
				traffic_graph[i] -> setTrafficWithMaxDeflectionOfBars( new_trafficoutwithmaxdeflectionofgraphs );
				break;
		}

}

//set the number identifying the device (for display only)
void Dev::setDeviceNumber( int new_devicenumber )
{
	m_devicenumber = new_devicenumber;
}

//set the total number of shown devices (for display only)
void Dev::setTotalNumberOfDevices( int new_totalnumberofdevices )
{
	m_totalnumberofdevices = new_totalnumberofdevices;
}

//set the display format (unit) for traffic and data numbers
void Dev::setStatusFormat( Status::status_format new_trafficformat, Status::status_format new_dataformat )
{
	m_trafficformat = new_trafficformat;
	m_dataformat = new_dataformat;
}
