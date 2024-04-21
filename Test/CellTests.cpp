//
// Created by Troja on 19/04/2024.
//

#include "gtest/gtest.h"
#include "objects/solver/Cell.h"

class CellTests : public ::testing::Test
{
protected:
    Cell cell, cell2;
    GridTextBox t;

    virtual void SetUp()
    {
      cell.empty(false);
      cell2.empty(false);
      t.setText("");
    }

    virtual void TearDown()
    {

    }
};


TEST_F(CellTests, markInsertRemove)
{
  cell.insertMark(5);

  ASSERT_TRUE(cell.isDigitMarked(5));
  ASSERT_EQ(1, cell.getNumberOfMarks());

  cell.removeMark(5);

  ASSERT_FALSE(cell.isDigitMarked(5));
  ASSERT_EQ(0, cell.getNumberOfMarks());

  ASSERT_FALSE(cell.removeMark(2));
}


TEST_F(CellTests, checkLoneMark)
{
  cell.insertMark(5);
  cell.insertMark(4);
  cell.insertMark(3);

  ASSERT_EQ(-1, cell.checkLoneMark());

  cell.removeMark(4);
  cell.removeMark(3);

  ASSERT_EQ(5, cell.checkLoneMark());
}


TEST_F(CellTests, solve)
{
  cell.solve(5);

  ASSERT_TRUE(cell.isSolved());
  ASSERT_EQ(5, cell.getFinalNumber());

  cell.empty(false);
  cell.solve(-1);

  ASSERT_FALSE(cell.isSolved());
  ASSERT_EQ(9, cell.getNumberOfMarks());

  cell.empty(false);
  cell.insertMark(4);
  cell.insertMark(3);
  cell.insertMark(2);
  cell.solve(5);
  ASSERT_EQ(0, cell.getNumberOfMarks());
}


TEST_F(CellTests, fillFromTextBox)
{
  t.setText("5");
  cell.addTextBox(&t);
  cell.fillFromTextBox(true);

  ASSERT_TRUE(cell.isSolved());
  ASSERT_EQ(4, cell.getFinalNumber());

  cell.empty(false);
  t.setText("");
  cell.fillFromTextBox(true);

  ASSERT_FALSE(cell.isSolved());
}

TEST_F(CellTests, empty)
{
  cell.insertMark(5);
  cell.insertMark(4);
  cell.insertMark(6);

  cell.empty(false);

  ASSERT_EQ(0, cell.getNumberOfMarks());

  cell.solve(5);
  cell.empty(false);
  ASSERT_FALSE(cell.isSolved());
}


TEST_F(CellTests, orMarksSolvedCell)
{
  cell.insertMark(5);
  cell.insertMark(4);
  cell.insertMark(3);

  cell2.solve(8);

  int orResults;
  bool* orResultBools = cell.orMarks(&cell2, orResults);

  ASSERT_EQ(9, orResults);
  for (int i = 0; i < 9; i++)
  {
    ASSERT_TRUE(orResultBools[i]);
  }
}

TEST_F(CellTests, orMarksCell)
{
  cell.insertMark(5);
  cell.insertMark(4);
  cell.insertMark(3);

  cell2.insertMark(5);
  cell2.insertMark(6);
  cell2.insertMark(7);

  int orResult;
  bool* orResultBools = cell.orMarks(&cell2, orResult);

  ASSERT_EQ(5, orResult);
  for (int i = 0; i < 9; i++)
  {
    if (i >= 3 && i <= 7)
      ASSERT_TRUE(orResultBools[i]);
    else
      ASSERT_FALSE(orResultBools[i]);
  }
}


TEST_F(CellTests, orMarksArray)
{
  cell.insertMark(5);
  cell.insertMark(4);
  cell.insertMark(3);

  bool arrayToOr[9];
  for (bool &digit: arrayToOr)
  {
    digit = false;
  }
  arrayToOr[5] = true;
  arrayToOr[6] = true;
  arrayToOr[7] = true;

  int orResult;
  bool* orResultBools = cell.orMarks(arrayToOr, orResult);

  ASSERT_EQ(5, orResult);
  for (int i = 0; i < 9; i++)
  {
    if (i >= 3 && i <= 7)
      ASSERT_TRUE(orResultBools[i]);
    else
      ASSERT_FALSE(orResultBools[i]);
  }
}


TEST_F(CellTests, fixLimitedMarks)
{
  cell.insertMark(2);
  cell.insertMark(3);
  cell.insertMark(4);
  cell.insertMark(5);

  cell2.insertMark(2);
  cell2.insertMark(4);

  bool limitedMarks[9];
  for (auto &digit: limitedMarks)
  {
    digit = false;
  }
  limitedMarks[2] = true;
  limitedMarks[4] = true;

  ASSERT_TRUE(cell.fixLimitedMarks(limitedMarks));
  ASSERT_FALSE(cell2.fixLimitedMarks(limitedMarks));

  ASSERT_FALSE(cell.isDigitMarked(2));
  ASSERT_FALSE(cell.isDigitMarked(4));
  ASSERT_TRUE(cell.isDigitMarked(3));
  ASSERT_TRUE(cell2.isDigitMarked(2));
  ASSERT_TRUE(cell2.isDigitMarked(4));

  cell.solve(5);
  ASSERT_FALSE(cell.fixLimitedMarks(limitedMarks));
}