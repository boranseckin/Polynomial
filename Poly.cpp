/**
 * @file Poly.cpp
 * @author Boran Seckin <seckinb@mcmaster.ca>
 * @author George Gill <gillg62@mcmaster.ca>
 */

#include <iostream>
#include <cmath>

#include "Poly.h"

/**
 * @brief Construct a new empty Poly object.
 */
Poly::Poly()
{
	// Create the dummy node
	head = new PolyNode(-1, 0, NULL);
}

/**
 * @brief Construct a new Poly object given a vector of degrees
 * and a vector of coefficients of same size.
 * 
 * @param deg A vector of degrees (non-negative integers)
 * @param coeff A vector of coefficients
 */
Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
	// Create the dummy node
	head = new PolyNode(-1, 0, NULL);

	PolyNode *current = head;

	// For every degree add a new node
	for (int i = 0; i < deg.size(); i++)
	{
		current->next = new PolyNode(deg[i], coeff[i], NULL);
		current = current->next;
		termsNo++;
	}
}

/**
 * @brief Destroy the Poly object by destroying all PolyNodes.
 */
Poly::~Poly()
{
	PolyNode *current = head;
	PolyNode *next;

	while (current != NULL)
	{
		next = current->next;
		delete current;
		current = next;
	}
}

/**
 * @brief Add a new PolyNode to the Poly object. If the degree exists,
 * the coefficient is added to the existing one. If the resulting coefficient
 * is zero, the node is deleted.
 * 
 * @param node A pointer to the new PolyNode
 */
void Poly::addNode(PolyNode *node)
{
	PolyNode *current = head;

	// Find the node with the same degree or the first node with a smaller degree
	while (current->next != NULL && current->next->deg >= node->deg)
	{
		current = current->next;
	}

	// If the node with the same degree exists, add the coefficients
	// Otherwise, insert a new node
	if (current->deg == node->deg) {
		current->coeff += node->coeff;

		// If the resulting coefficient is zero, delete the node
		if (current->coeff == 0) {
			deleteNode(current->deg);
		}

		// This node is not part of the list, delete it
		delete node;
	} else {
		node->next = current->next;
		current->next = node;
		termsNo++;
	}
}

/**
 * @brief Delete the PolyNode with the given degree.
 * 
 * @param deg A degree of the PolyNode to be deleted
 */
void Poly::deleteNode(int deg)
{
	PolyNode *current = head;

	// Find the node with the same degree
	while (current->next != NULL && current->next->deg != deg)
	{
		current = current->next;
	}

	// If the node with the same degree doesn't exists throw error
	if (current->next == NULL)
	{
		throw std::domain_error("No node with degree " + std::to_string(deg) + " found.");
	}

	// Delete the node
	PolyNode *next = current->next->next;
	delete current->next;
	current->next = next;

	termsNo--;
}

/**
 * @brief Adds a new monomial to this Poly object.
 * 
 * @param i Degree of the monomial
 * @param c Coefficient of the monomial
 */
void Poly::addMono(int i, double c)
{
	if (c == 0) return;

	PolyNode *node = new PolyNode(i, c, NULL);
	addNode(node);
}

/**
 * @brief Adds a Poly object to this Poly object.
 * 
 * @param p Poly object to be added
 */
void Poly::addPoly(const Poly& p)
{
	if (p.termsNo == 0) return;

	PolyNode *current = p.head->next;

	while (current != NULL)
	{
		addMono(current->deg, current->coeff);
		current = current->next;
	}
}

/**
 * @brief Multiplies a monomial with this Poly object.
 * 
 * @param i Degree of the monomial
 * @param c Coefficient of the monomial
 */
void Poly::multiplyMono(int i, double c)
{	
	PolyNode *current = head->next;

	while (current != NULL)
	{
		// If the coefficient of the monomial is zero, delete the node
		if (c == 0) {
			deleteNode(current->deg);
		} else {
			current->deg += i;
			current->coeff *= c;
		}

		current = current->next;
	}

}

/**
 * @brief Multiplies a Poly object with this Poly object.
 * 
 * @param p Poly object to be multiplied
 */
void Poly::multiplyPoly(const Poly& p)
{
	PolyNode *current = head->next;
	PolyNode *currentP = p.head->next;

	// If either of the Poly objects is empty, delete all nodes and return
	if (p.termsNo == 0 || termsNo == 0) {
		while (current != NULL) {
			deleteNode(current->deg);
			current = current->next;
		}
		return;
	}

	// Keep track of the initial condition of this Poly object
	int *toBeDeletedDeg = new int[termsNo];
	int *toBeDeletedCoeff = new int[termsNo];
	int i = 0;

	while (current != NULL)
	{
		// Save the this node's degree and coefficient before multiplying
		toBeDeletedDeg[i] = current->deg;
		toBeDeletedCoeff[i] = current->coeff;

		// Multiply the current term with the given Poly object
		while (currentP != NULL)
		{
			addMono(current->deg + currentP->deg, current->coeff * currentP->coeff);
			currentP = currentP->next;
		}

		// Proceed to the next term and reset the currentP pointer
		current = current->next;
		currentP = p.head->next;
		i++;
	}

	/**
	 * Subtract the initial condition of this Poly object. This way, 
	 * if a term with the same degree is added during multiplication it will not be deleted.
	 */
	for (int j = 0; j < i; j++) {
		addMono(toBeDeletedDeg[j], -toBeDeletedCoeff[j]);
	}

	delete[] toBeDeletedDeg;
	delete[] toBeDeletedCoeff;
}

/**
 * @brief Duplicates this Poly object.
 * 
 * @param outputPoly A pointer to the Poly object to be duplicated
 */
void Poly::duplicate(Poly& outputPoly)
{
	PolyNode *current = head->next;

	while (current != NULL)
	{
		outputPoly.addMono(current->deg, current->coeff);
		current = current->next;
	}
}

/**
 * @brief Return the degree of the Poly object.
 * 
 * @return int The degree of the Poly object
 */
int Poly::getDegree()
{
	return head->next ? head->next->deg : head->deg;
}

/**
 * @brief Return the number of terms in the Poly object.
 * 
 * @return int Returns the number of terms in the Poly object
 */
int Poly::getTermsNo()
{
	return termsNo;
}

/**
 * @brief Evaluate the Poly object at the given x.
 * 
 * @param x A value to evaluate the Poly object at
 * @return double The value of the Poly object at x
 */
double Poly::evaluate(double x)
{
	double result = 0;

	PolyNode *current = head->next;
	while (current != NULL)
	{
		result += current->coeff * std::pow(x, current->deg);
		current = current->next;
	}

	return result;
}

/**
 * @brief Return the string representation of the Poly object.
 * 
 * @return std::string The string representation of the Poly object
 */
std::string Poly::toString()
{
	std::string result = "degree=";
	result += std::to_string(getDegree());
	
	PolyNode *current = head->next;
	while(current != NULL)
	{
		result += "; a(";
		result += std::to_string(current->deg);
		result += ")=";
		result += std::to_string(current->coeff);
		current = current->next;
	}

	return result;
}
