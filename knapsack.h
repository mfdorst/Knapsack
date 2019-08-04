//===-- knapsack.h - 0/1 Knapsack Problem solver ----------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===----------------------------------------------------------------------===//
/// \file
/// This file contains the declrations of all classes and functions pertaining
/// to solving the 0/1 knapsack problem.
//===----------------------------------------------------------------------===//

//#define KNAPSACK_DEBUG

#define INVALID_VALUE -1

enum UPPER_BOUND { UB1, UB2, UB3 };

class KnapsackInstance
{
private:
	int itemCnt; //Number of items
	int cap; //The capacity
	int* weights;//An array of weights
	int* values;//An array of values

public:
	KnapsackInstance(int itemCnt_);
	~KnapsackInstance();

	void Generate();

	int GetItemCnt();
	int GetItemWeight(int itemNum);
	int GetItemValue(int itemNum);
	int GetCapacity();
	void Print();
};

class KnapsackSolution
{
private:
	bool* isTaken;
	int value;
	int wght;
	KnapsackInstance* inst;

public:
	KnapsackSolution(KnapsackInstance* inst);
	~KnapsackSolution();

	bool operator == (KnapsackSolution& otherSoln);
	void TakeItem(int itemNum);
	void DontTakeItem(int itemNum);
	int ComputeValue();
	int GetValue();
	int GetWeight();
	void Print(std::string str);
	void Copy(KnapsackSolution* otherSoln);
};

// Dynamic programming solver
class KnapsackDPSolver
{
private:
	KnapsackInstance* inst;
	KnapsackSolution* soln;

public:
	KnapsackDPSolver();
	~KnapsackDPSolver();
	void Solve(KnapsackInstance* inst, KnapsackSolution* soln);
};


// Brute-force solver
class KnapsackBFSolver
{
protected:
	KnapsackInstance* inst;
	KnapsackSolution* crntSoln;
	KnapsackSolution* bestSoln;

	virtual void FindSolns(int itemNum);
	virtual void CheckCrntSoln();

public:
	KnapsackBFSolver();
	~KnapsackBFSolver();
	virtual void Solve(KnapsackInstance* inst, KnapsackSolution* soln);
};


// Backtracking solver
class KnapsackBTSolver: public KnapsackBFSolver
{

public:
	KnapsackBTSolver();
	~KnapsackBTSolver();
	void Solve(KnapsackInstance* inst, KnapsackSolution* soln);
};

// Branch-and-Bound solver
class KnapsackBBSolver: public KnapsackBFSolver
{
protected:
enum UPPER_BOUND ub;

public:
	KnapsackBBSolver(enum UPPER_BOUND ub_);
	~KnapsackBBSolver();
	void Solve(KnapsackInstance* inst, KnapsackSolution* soln);
};

