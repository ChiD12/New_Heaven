#include "Player.h"
#include <string>
#include <iostream>

class GBMap;

Player::Player(std::string given_name, HarvestDeck given_hdeck, BuildingDeck given_bdeck) {
	this->name = given_name;

	name_ptr = &name;

	resource_handler = new ResourceHandler();

	building_hand = new vector<BuildingTile*>();
	harvest_hand = new vector<HarvestTile*>();

	player_board = new VGMap();

	cout << "I'm going to draw my cards" << endl;

	this->DrawHarvestTile(2, given_hdeck);

	cout << "I've drawn my harvest tiles and will now draw my building tiles.." << endl;

	this->DrawBuilding(6, given_bdeck);

	cout << this->name << " drew their starting cards" << endl;

}

Player::~Player()
{
	delete (resource_handler, building_hand, harvest_hand, player_board);
}

bool Player::PlaceHarvestTile(GBMap* given_board, HarvestTile* given_tile, int tl_x, int tl_y)
{
	if ((*given_board).PlaceTile(given_tile, tl_x, tl_y)) { //If the tile has been placed successfully.
		this->CalculateResources(given_board, tl_x, tl_y); //Calculate the resources we just got.
		return true;
	}
	else return false;
}

void Player::DrawBuilding(int number_of_cards, BuildingDeck given_deck)
{
	for (int i = 0; i < number_of_cards; i++) {
		this->building_hand->push_back(given_deck.DrawBuildingTile()); //Draw a building tile from the "deck" and add it to the hand vector. Do this for as many cards are requested.
		cout << "I've drawn building card " << i << "." << endl;
	}
	cout << "I've finished drawing my building tiles" << endl;
}

void Player::DrawHarvestTile(int number_of_cards, HarvestDeck given_deck)
{

	for (int i = 0; i < number_of_cards; i++) {
		this->harvest_hand->push_back(given_deck.DrawHarvestTile()); //Draw a building tile from the "deck" and add it to the hand vector. Do this for as many cards are requested.
		cout << "I've drawn harvest card " << i << "." << endl;
	}
	cout << "I've finished drawing my harvest tiles" << endl;
}

void Player::ResourceTracker()
{
	this->resource_handler->PrintResources();
}

void Player::BuildVillage(int given_x, int given_y, BuildingTile given_tile)
{
	player_board->placeTile(given_x, given_y, given_tile);
}

void Player::CalculateResources(GBMap* given_board, int tl_x, int tl_y)
{
	vector<int> acquired_resources = (*given_board).CalculateResources(tl_x, tl_y);

	this->resource_handler->total_wood = acquired_resources[0];
	this->resource_handler->total_grain = acquired_resources[1];
	this->resource_handler->total_sheep = acquired_resources[2];
	this->resource_handler->total_stone = acquired_resources[3];
}

void Player::PrintHarvestHand()
{
	cout << "These are the harvest tiles I have: " << endl;
	for (HarvestTile* harvest_tile : *harvest_hand)
	{
		harvest_tile->PrintHarvestTile();
	}
}

void Player::PrintBuildingHand()
{
	cout << "These are the building tiles I have: " << endl;
	for (BuildingTile* building_tile : *building_hand)
	{
		building_tile->PrintBuildingTile();
	}
}

ResourceHandler::ResourceHandler() //We can assume a player starts with no resources.
{
	this->total_wood = 0;
	tw_ptr = &total_wood;
	this->total_grain = 0;
	tg_ptr = &total_grain;
	this->total_sheep = 0;
	tsh_ptr = &total_sheep;
	this->total_stone = 0;
	tst_ptr = &total_stone;
}

void ResourceHandler::PrintResources()
{
	cout << "The resources I am currently holding are as follows: " << "WOOD: " << *tw_ptr << " |GRAIN: " << *tg_ptr << " |SHEEP: " << *tsh_ptr << " |STONE: " << *tst_ptr << endl;
}

ResourceHandler::~ResourceHandler()
{

}

