#include <iostream>
#include <cmath>

#include "Poly.h"

Poly::Poly()
{
	head = new PolyNode(-1, 0, NULL);
}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
	head = new PolyNode(-1, 0, NULL);

	PolyNode *current = head;

	for (int i = 0; i < deg.size(); i++)
	{
		current->next = new PolyNode(deg[i], coeff[i], NULL);
		current = current->next;
		termsNo++;
	}
}

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

void Poly::addNode(PolyNode *node)
{
	PolyNode *current = head;

	while (current->next != NULL && current->next->deg >= node->deg)
	{
		current = current->next;
	}

	if (current->deg == node->deg) {
		current->coeff += node->coeff;

		if (current->coeff == 0) {
			deleteNode(current->deg);
			delete node;
		}
	} else {
		node->next = current->next;
		current->next = node;
		termsNo++;
	}
}

void Poly::deleteNode(int deg)
{
	PolyNode *current = head;

	while (current->next != NULL && current->next->deg != deg)
	{
		current = current->next;
	}

	if (current->next == NULL)
	{
		throw std::domain_error("No node with degree " + std::to_string(deg) + " found.");
	}

	PolyNode *next = current->next->next;
	delete current->next;
	current->next = next;

	termsNo--;
}

void Poly::addMono(int i, double c)
{
	// TODO
}

void Poly::addPoly(const Poly& p)
{
	// TODO
}

void Poly::multiplyMono(int i, double c)
{
	// TODO
}

void Poly::multiplyPoly(const Poly& p)
{
	// TODO
}

void Poly::duplicate(Poly& outputPoly)
{
	// TODO
}

int Poly::getDegree()
{
	return head->next ? head->next->deg : head->deg;
}

int Poly::getTermsNo()
{
	return termsNo;
}

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
