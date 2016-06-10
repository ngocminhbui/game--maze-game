#include "Block.h"

int Block::_color;


void Block::setColor(int color){
	_color = color;
}

Block::Block(pair<int, int> position):IMapObject(position){
	_position = position;
}

string Block::getType(){
	return "block";
}

DrawCommand Block::draw(){
	return DrawCommand(_position, _color, stoi(GameConfig::getConfig("backgroundColor")), '\#');
}