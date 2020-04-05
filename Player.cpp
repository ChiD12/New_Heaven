#include "Player.h"
#include <string>
#include <iostream>

class GBMap;


Player::Player(std::string given_name, int given_id,  HarvestDeck given_hdeck, BuildingDeck given_bdeck) {
	this->name = new string(given_name);
	this->id = new int(given_id);

	building_hand = new vector<BuildingTile*>();
	harvest_hand = new vector<HarvestTile*>();

	player_board = new VGMap();

	cout << *this->name << " is going to draw their starting tiles!" << endl;

	this->DrawHarvestTile(2, given_hdeck);

	cout << *this->name << " is taking their shipment tile, how mysterious!" << endl;

	this->shipment_tile = given_hdeck.DrawHarvestTile();

	this->has_shipment = new bool(true);

	cout << *this->name << " has drawn their harvest tiles and will now draw their building tiles.." << endl;

	this->DrawBuilding(6, given_bdeck);



	cout << *this->name << " drew their starting tiles" << endl;
}

Player::~Player()
{
	delete id;
	delete name;
	delete player_board;
	delete has_shipment;
	delete shipment_tile;
	id = nullptr;
	name = nullptr;
	player_board = nullptr;
	has_shipment = nullptr;
	shipment_tile = nullptr;

	building_hand->clear();
	harvest_hand->clear();
}

void Player::exchange(GBMap* given_board, int given_x, int given_y)
{
	vector<int> res = given_board->CalculateResources(given_x, given_y);
	*(given_board->RMWood) = res.at(0);
	*(given_board->RMGrain) = res.at(1);
	*(given_board->RMSheep) = res.at(2);
	*(given_board->RMStone) = res.at(3);
	cout << "GameBoard resources updated!" << endl;
	//given_board->PrintResources();
}

bool Player::PlaceHarvestTile(GBMap* given_board, int hand_index, int tl_x, int tl_y)
{
	if ((*given_board).PlaceTile(harvest_hand->at(hand_index), tl_x, tl_y)) { //If the tile has been placed successfully.
		harvest_hand->erase(harvest_hand->begin() + hand_index);
		this->exchange(given_board, tl_x, tl_y); //Calculate the resources we just got.
		return true;
	}
	else return false;
}

bool Player::PlaceShipmentTile(GBMap * given_board, int resource_index, int given_x, int given_y)
{
	HarvestTile* place_me = new HarvestTile(resource_index, resource_index, resource_index, resource_index);

	if (given_board->PlaceTile(place_me, given_x, given_y) == true) {
		exchange(given_board, given_x, given_y);
		delete has_shipment;
		this->has_shipment = new bool(false);
		return true;
	}
	else {return false;}
}

void Player::DrawBuilding(int number_of_cards, BuildingDeck given_deck)
{
	for (int i = 0; i < number_of_cards; i++) {
		cout << *this->name << " is drawing a building tile!" << endl;
		this->building_hand->push_back(given_deck.DrawBuildingTile()); //Draw a building tile from the "deck" and add it to the hand vector. Do this for as many cards are requested.
		
	}
}

void Player::DrawHarvestTile(int number_of_cards, HarvestDeck given_deck)
{

	for (int i = 0; i < number_of_cards; i++) {
		cout << *this->name << " is drawing a harvest tile!" << endl;
		this->harvest_hand->push_back(given_deck.DrawHarvestTile()); //Draw a building tile from the "deck" and add it to the hand vector. Do this for as many cards are requested.
		
	}
	
}

void Player::ResourceTracker()
{

}

bool Player::BuildVillage(int given_x, int given_y, int hand_index, bool flipped)
{
	if (player_board->placeTile(given_x, given_y, flipped, *building_hand->at(hand_index))) {
		// remove tile that was played from hand	
		building_hand->erase(building_hand->begin() + (hand_index));
		return true;
	}
	else return false;
}

void Player::CalculateResources(GBMap* given_board, int tl_x, int tl_y)
{
	(*given_board).CalculateResources(tl_x, tl_y);
}
 
void Player::PrintHarvestHand()
{
	cout << "These are the harvest tiles I have: " << endl;
	int counter = 1;
	for (HarvestTile* harvest_tile : *harvest_hand) {
		cout << "   " << counter++ << "   " << endl;
		harvest_tile->PrintHarvestTile();
		cout << endl;
	}

	if (*this->has_shipment == true) {
		cout << "   " << harvest_hand->size()+1 << "   " << endl;
		cout << "[?]" << "[?]" << endl;
		cout << "[?]" << "[?]" << endl;
	}
}

void Player::PrintBuildingHand()
{
	cout << "These are the building tiles I have: " << endl;
	for (int i = 0; i < building_hand->size(); i++) {
		cout << (i + 1) << ":";
		building_hand->at(i)->PrintBuildingTile();
		cout << "  ";
	}
	cout << endl;
}
