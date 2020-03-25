#include "Player.h"
#include <string>
#include <iostream>

class GBMap;

Player::Player(std::string given_name, int given_id, HarvestDeck given_hdeck, BuildingDeck given_bdeck) {
	this->name = new string(given_name);
	this->id = new int(given_id);

	building_hand = new vector<BuildingTile*>();
	harvest_hand = new vector<HarvestTile*>();

	player_board = new VGMap();

	cout << "I'm going to draw my cards" << endl;

	this->DrawHarvestTile(2, given_hdeck);

	cout << "I've drawn my harvest tiles and will now draw my building tiles.." << endl;

	this->DrawBuilding(6, given_bdeck);

	cout << "There are now " << given_bdeck.GetCardCount() << " cards left in the building deck." << endl;

	cout << *this->name << " drew their starting cards" << endl;

}

Player::~Player()
{
	delete id;
	delete name;
	id = nullptr;
	name = nullptr;
}

void Player::exchange(GBMap* given_board, int given_x, int given_y)
{
	this->CalculateResources(given_board, given_x, given_y);
	cout << "GameBoard resources updated!" << endl;
	given_board->PrintResources();
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

}

bool Player::BuildVillage(int given_x, int given_y, bool flipped, BuildingTile given_tile)
{
	return player_board->placeTile(given_x, given_y, flipped, given_tile);
}

void Player::CalculateResources(GBMap* given_board, int tl_x, int tl_y)
{
	(*given_board).CalculateResources(tl_x, tl_y);
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


