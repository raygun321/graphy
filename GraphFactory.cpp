#include <GraphFactory.h>
#include <Utility.h>
#include <Vector2.h>
#include <stack>
#include <iostream>

GraphFactory::GraphFactory() :
_stepDistance(1.0),
_turnAngle(90.0)
{
}


GraphFactory::GraphFactory(double step, double turn) :
        _stepDistance(step),
        _turnAngle(turn)
{
}

GraphFactory::~GraphFactory() { }

struct GraphState
{
	bool   notFirst;
	Vertex currentVertex;
	Vector2d heading;
	Vector2d position;
};

Graph GraphFactory::generate(const std::string & pattern) const {
	Graph g;
	GraphState state;
    std::stack<GraphState> stateStack;

    state.heading = Vector2d(0, 0 - _stepDistance);
    state.position = Vector2d(0, 0);
    state.notFirst = false;

    for(const char& c : pattern) {
//        std::cout << std::endl << c << ": ";
        switch(c) {
        case '<':
//                std::cout << " Old Heading: " << state.heading;
        	state.heading = state.heading.rotate(0 - _turnAngle);
//		std::cout << " New Heading: " << state.heading;
        	break;
        case '>':
//                std::cout << " Old Heading: " << state.heading;
        	state.heading = state.heading.rotate( _turnAngle);
//                std::cout << " New Heading: " << state.heading;
        	break;
        case '[':
        	// Push heading, position, and current node
        	stateStack.push(state);
//                std::cout << " New Position: " << state.position;
//                std::cout << " New Heading: " << state.heading; 
        	break;
        case ']':
        	state = stateStack.top();
        	stateStack.pop();
//                std::cout << " New Position: " << state.position;
//                std::cout << " New Heading: " << state.heading;
        	break;
        case 'F':
                // move and create a node
//                std::cout << " Old Position: " << state.position;
                state.position += state.heading;
//                std::cout << " New Position: " << state.position;
        default:
        	// Create a node
            Vertex newVertex = boost::add_vertex(g);

            g[newVertex].label = c;
            g[newVertex].position = state.position;

            // If not the first node, create a link between this and the last node
            if(state.notFirst) {
                boost::add_edge(newVertex, state.currentVertex, g);
            } else {
            	state.notFirst = true;
            }

            state.currentVertex = newVertex;
        }
    }
	
	return g;	
}

