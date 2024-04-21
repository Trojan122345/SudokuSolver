//
// Created by Troja on 19/04/2024.
//

#include <gtest/gtest.h>
#include "objects/solver/NineSet.h"

class NineSetTests : public ::testing::Test
{
protected:
    NineSet set;
    Cell cells[9];

    virtual void SetUp()
    {
      for (int i = 0; i < 9; i++)
      {
        cells[i].empty(false);
        set.addCell(&cells[i]);
        set.reset();
      }
    }

    virtual void TearDown()
    {

    }


};

TEST_F(NineSetTests, checkLastNumber)
{
  for (int i = 0; i < 8; i++)
  {
    set.solveCell(i, i);
  }

  bool result = set.checkLastNumber();

  ASSERT_TRUE(result);
  ASSERT_EQ(8, cells[8].getFinalNumber());
}


TEST_F(NineSetTests, checkOnlyMark)
{
  for (int i = 0; i < 8; i++)
  {
    cells[i].insertMark(1);
    cells[i].insertMark(2);
    cells[i].insertMark(5);
  }

  cells[8].insertMark(3);

  bool result = set.checkOnlyMark();

  ASSERT_TRUE(result);
  ASSERT_EQ(3, cells[8].getFinalNumber());
}


TEST_F(NineSetTests, checkSingleRow)
{
  for (int i = 0; i < 6; i++)
  {
    cells[i].insertMark(1);
    cells[i].insertMark(2);
    cells[i].insertMark(5);
  }
  for (int i = 6; i < 9; i++)
  {
    cells[i].insertMark(6);
  }

  int rowRet, colRet;
  bool result = set.checkSingleRowCol(rowRet, colRet, 6);

  ASSERT_TRUE(result);
  ASSERT_EQ(2, rowRet);
  ASSERT_EQ(-1, colRet);
}


TEST_F(NineSetTests, checkSingleCol)
{
  for (int i = 0; i < 6; i++)
  {
    if (i % 3 == 2)
    {
      cells[i].insertMark(6);
    }
    else
    {
      cells[i].insertMark(1);
      cells[i].insertMark(2);
      cells[i].insertMark(5);
    }
  }

  int rowRet, colRet;
  bool result = set.checkSingleRowCol(rowRet, colRet, 6);

  ASSERT_TRUE(result);
  ASSERT_EQ(-1, rowRet);
  ASSERT_EQ(2, colRet);
}

TEST_F(NineSetTests, limitedMarksDepth2)
{
  set.solveCell(0, 0);
  set.solveCell(1, 1);
  set.solveCell(2, 2);

  int cell34marks[2] = {3, 4};
  int cell5marks[2] = {5, 6};
  int cell6marks[2] = {7, 8};
  int cell7marks[2] = {5, 7};
  int cell8marks[3] = {6, 7, 8};

  for (int i = 0; i < 3; i++)
  {
    if (i < 2)
    {
      cells[3].insertMark(cell34marks[i]);
      cells[4].insertMark(cell34marks[i]);
      cells[5].insertMark(cell5marks[i]);
      cells[6].insertMark(cell6marks[i]);
      cells[7].insertMark(cell7marks[i]);
      cells[8].insertMark(cell8marks[i]);
    }
    else
      cells[8].insertMark(cell8marks[i]);
  }

  cells[5].insertMark(3);
  cells[6].insertMark(4);
  cells[7].insertMark(3);
  cells[7].insertMark(4);

  EXPECT_TRUE(set.checkLimitedMarks());

  for (int i = 0; i < 3; i++)
  {
    if (i < 2)
    {
      EXPECT_TRUE(cells[3].isDigitMarked(cell34marks[i]));
      EXPECT_TRUE(cells[4].isDigitMarked(cell34marks[i]));
      EXPECT_TRUE(cells[5].isDigitMarked(cell5marks[i]));
      EXPECT_TRUE(cells[6].isDigitMarked(cell6marks[i]));
      EXPECT_TRUE(cells[7].isDigitMarked(cell7marks[i]));
      EXPECT_TRUE(cells[8].isDigitMarked(cell8marks[i]));

      EXPECT_FALSE(cells[5].isDigitMarked(cell34marks[i]));
      EXPECT_FALSE(cells[6].isDigitMarked(cell34marks[i]));
      EXPECT_FALSE(cells[7].isDigitMarked(cell34marks[i]));
      EXPECT_FALSE(cells[8].isDigitMarked(cell34marks[i]));
    }
    else
      ASSERT_TRUE(cells[8].isDigitMarked(cell8marks[i]));
  }
}


TEST_F(NineSetTests, limitedMarksDepth3)
{
  set.solveCell(0, 0);
  set.solveCell(1, 1);
  set.solveCell(2, 2);

  int cell345marks[3] = {3, 4, 5};
  int cell678marks[3] = {6, 7, 8};

  for (int i = 0; i < 3; i++)
  {
    if (i != 2)
      cells[3].insertMark(cell345marks[i]);
    if (i != 1)
      cells[4].insertMark(cell345marks[i]);
    if (i != 0)
      cells[5].insertMark(cell345marks[i]);

    cells[6].insertMark(cell678marks[i]);
    cells[7].insertMark(cell678marks[i]);
    cells[8].insertMark(cell678marks[i]);
  }

  cells[6].insertMark(3);
  cells[7].insertMark(5);
  cells[8].insertMark(4);
  cells[8].insertMark(5);

  EXPECT_TRUE(set.checkLimitedMarks());

  for (int i = 0; i < 3; i++)
  {
    if (i != 2)
      EXPECT_TRUE(cells[3].isDigitMarked(cell345marks[i]));
    if (i != 1)
      EXPECT_TRUE(cells[4].isDigitMarked(cell345marks[i]));
    if (i != 0)
      EXPECT_TRUE(cells[5].isDigitMarked(cell345marks[i]));
    EXPECT_TRUE(cells[6].isDigitMarked(cell678marks[i]));
    EXPECT_TRUE(cells[7].isDigitMarked(cell678marks[i]));
    EXPECT_TRUE(cells[8].isDigitMarked(cell678marks[i]));

    EXPECT_FALSE(cells[6].isDigitMarked(cell345marks[i]));
    EXPECT_FALSE(cells[7].isDigitMarked(cell345marks[i]));
    EXPECT_FALSE(cells[8].isDigitMarked(cell345marks[i]));
  }
}


TEST_F(NineSetTests, limitedMarksDouble)
{
  cells[0].insertMark(0);
  cells[0].insertMark(1);
  cells[1].insertMark(0);
  cells[1].insertMark(1);

  cells[2].insertMark(2);
  cells[2].insertMark(3);
  cells[3].insertMark(3);
  cells[3].insertMark(4);
  cells[4].insertMark(4);
  cells[4].insertMark(5);
  cells[5].insertMark(5);
  cells[5].insertMark(2);

  cells[6].insertMark(1);
  cells[6].insertMark(4);
  cells[6].insertMark(5);
  cells[7].insertMark(0);
  cells[7].insertMark(2);
  cells[7].insertMark(3);
  cells[7].insertMark(4);
  for (int i = 6; i < 9; i++)
  {
    cells[6].insertMark(i);
    cells[7].insertMark(i);
  }
  for (int i = 0; i < 9; i++)
  {
    cells[8].insertMark(i);
  }

  EXPECT_TRUE(set.checkLimitedMarks());

  for (int i = 0; i < 2; i++)
  {
    EXPECT_TRUE(cells[0].isDigitMarked(i));
    EXPECT_TRUE(cells[1].isDigitMarked(i));
  }
  for (int i = 6; i < 9; i++)
  {
    EXPECT_TRUE(cells[6].isDigitMarked(i));
    EXPECT_TRUE(cells[7].isDigitMarked(i));
    EXPECT_TRUE(cells[8].isDigitMarked(i));
  }
  for (int i = 0; i < 6; i++)
  {
    EXPECT_FALSE(cells[6].isDigitMarked(i));
    EXPECT_FALSE(cells[7].isDigitMarked(i));
    EXPECT_FALSE(cells[8].isDigitMarked(i));
  }

  EXPECT_TRUE(cells[2].isDigitMarked(2));
  EXPECT_TRUE(cells[2].isDigitMarked(3));
  EXPECT_TRUE(cells[3].isDigitMarked(3));
  EXPECT_TRUE(cells[3].isDigitMarked(4));
  EXPECT_TRUE(cells[4].isDigitMarked(4));
  EXPECT_TRUE(cells[4].isDigitMarked(5));
  EXPECT_TRUE(cells[5].isDigitMarked(5));
  EXPECT_TRUE(cells[5].isDigitMarked(2));
}


TEST_F(NineSetTests, limitedCells2depth)
{
  set.solveCell(0, 0);
  set.solveCell(1, 1);
  set.solveCell(2, 2);

  cells[3].insertMark(3);
  cells[3].insertMark(4);
  cells[3].insertMark(5);
  cells[3].insertMark(7);
  cells[4].insertMark(3);
  cells[4].insertMark(4);
  cells[4].insertMark(6);
  cells[4].insertMark(8);
  cells[5].insertMark(5);
  cells[5].insertMark(6);
  cells[6].insertMark(6);
  cells[6].insertMark(7);
  cells[7].insertMark(7);
  cells[7].insertMark(8);
  cells[8].insertMark(5);
  cells[8].insertMark(6);
  cells[8].insertMark(7);
  cells[8].insertMark(8);



  EXPECT_TRUE(set.checkLimitedMarks());

  for (int i = 3; i < 5; i++)
  {
    EXPECT_TRUE(cells[3].isDigitMarked(i));
    EXPECT_TRUE(cells[4].isDigitMarked(i));
  }

  EXPECT_TRUE(cells[5].isDigitMarked(5));
  EXPECT_TRUE(cells[5].isDigitMarked(6));
  EXPECT_TRUE(cells[6].isDigitMarked(6));
  EXPECT_TRUE(cells[6].isDigitMarked(7));
  EXPECT_TRUE(cells[7].isDigitMarked(7));
  EXPECT_TRUE(cells[7].isDigitMarked(8));
  EXPECT_TRUE(cells[8].isDigitMarked(5));
  EXPECT_TRUE(cells[8].isDigitMarked(6));
  EXPECT_TRUE(cells[8].isDigitMarked(7));
  EXPECT_TRUE(cells[8].isDigitMarked(8));

  EXPECT_FALSE(cells[3].isDigitMarked(5));
  EXPECT_FALSE(cells[3].isDigitMarked(7));
  EXPECT_FALSE(cells[4].isDigitMarked(6));
  EXPECT_FALSE(cells[4].isDigitMarked(8));
}
