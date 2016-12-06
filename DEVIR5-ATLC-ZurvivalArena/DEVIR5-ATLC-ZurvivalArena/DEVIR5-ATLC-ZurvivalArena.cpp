//// DEVIR5-ATLC-ZurvivalArena.cpp : définit le point d'entrée pour l'application.
////
//
#include "stdafx.h"
#include <iostream>
#include "DEVIR5-ATLC-ZurvivalArena.h"
//#include "Character.h"
//#include "Position.h"
//#include <SFML\Graphics.hpp>
//
//#define MAX_LOADSTRING 100
//
//// Variables globales :
//HINSTANCE hInst;                                // instance actuelle
//WCHAR szTitle[MAX_LOADSTRING];                  // Le texte de la barre de titre
//WCHAR szWindowClass[MAX_LOADSTRING];            // le nom de la classe de fenêtre principale
//
//// Pré-déclarations des fonctions incluses dans ce module de code :
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPWSTR    lpCmdLine,
//	_In_ int       nCmdShow)
//{
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//
//	// TODO: placez ici le code.
//
//	std::cout << "Salut!" << std::endl;
//
//	// Initialise les chaînes globales
//	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//	LoadStringW(hInstance, IDC_DEVIR5ATLCZURVIVALARENA, szWindowClass, MAX_LOADSTRING);
//	MyRegisterClass(hInstance);
//
//	// Effectue l'initialisation de l'application :
//	if (!InitInstance(hInstance, nCmdShow))
//	{
//		return FALSE;
//	}
//
//	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEVIR5ATLCZURVIVALARENA));
//
//	MSG msg;
//
//	// Boucle de messages principale :
//	while (GetMessage(&msg, nullptr, 0, 0))
//	{
//		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//	}
//
//	return (int)msg.wParam;
//}
//
//
//
////
////  FONCTION : MyRegisterClass()
////
////  BUT : inscrit la classe de fenêtre.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEXW wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = WndProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = hInstance;
//	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEVIR5ATLCZURVIVALARENA));
//	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEVIR5ATLCZURVIVALARENA);
//	wcex.lpszClassName = szWindowClass;
//	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//	return RegisterClassExW(&wcex);
//}
//
////
////   FONCTION : InitInstance(HINSTANCE, int)
////
////   BUT : enregistre le handle de l'instance et crée une fenêtre principale
////
////   COMMENTAIRES :
////
////        Dans cette fonction, nous enregistrons le handle de l'instance dans une variable globale, puis
////        créons et affichons la fenêtre principale du programme.
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//	hInst = hInstance; // Stocke le handle d'instance dans la variable globale
//
//	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//	if (!hWnd)
//	{
//		return FALSE;
//	}
//
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//
//	return TRUE;
//}
//
////
////  FONCTION : WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  BUT :  traite les messages pour la fenêtre principale.
////
////  WM_COMMAND - traite le menu de l'application
////  WM_PAINT - dessine la fenêtre principale
////  WM_DESTROY - génère un message d'arrêt et retourne
////
////
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_COMMAND:
//	{
//		int wmId = LOWORD(wParam);
//		// Analyse les sélections de menu :
//		switch (wmId)
//		{
//		case IDM_ABOUT:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//	}
//	break;
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps;
//		HDC hdc = BeginPaint(hWnd, &ps);
//		// TODO: ajoutez le code de dessin qui utilise hdc ici...
//		EndPaint(hWnd, &ps);
//	}
//	break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}
//
//// Gestionnaire de messages pour la boîte de dialogue À propos de.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//		{
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		break;
//	}
//	return (INT_PTR)FALSE;
//}


#include <cstdlib>
#include <SFML\Graphics\Shape.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Rect.hpp>


#pragma region variables
sf::RenderWindow window;
sf::RectangleShape rect;
#pragma endregion variables

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	window.create(sf::VideoMode(400, 300), "VIEW");
	window.setPosition(sf::Vector2i(192, 0));
	window.setFramerateLimit(60);

	//	rect.setSize(10,32);
//	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works !");
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		//window.draw(shape);
		window.display();
	}
}
