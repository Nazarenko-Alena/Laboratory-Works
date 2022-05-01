#include "dividing-by-layers.hpp"
#include "base-types.hpp"

nazarenko::MatrixShape nazarenko::divideByLayers(const nazarenko::Shape::ShapeArray& array, size_t countArray)
{
  nazarenko::MatrixShape matrix;

  if (array == nullptr)
  {
    return matrix;
  }

  for (size_t n = 0; n < countArray; n++)
  {
    nazarenko::Shape::ShapePtr shape = array[n];
    bool rowFound = false;
    int count = 0;

    if (matrix.getNumberOfLines() == 0)
    {
      matrix.addLine().add(shape);
      continue;
    }
    else
    {
      for (int i = (matrix.getNumberOfLines() - 1); i >= 0 && (rowFound == false) && (count == 0); i--)
      {
        for (size_t j = 0; j < matrix[i].getSize(); j++)
        {
          if (matrix[i][j])
          {
            if (details::checkingOverlapRect(matrix[i][j]->getFrameRect(), shape->getFrameRect()))
            {
              const int k = matrix.getNumberOfLines() - 1;
              count++;
              if (i != k)
              {
                matrix[i + 1].add(shape);
                rowFound = true;
                continue;
              }
            }
          }
        }
      }

      if (!rowFound && (count == 1))
      {
        matrix.addLine().add(shape);
        rowFound = true;
        continue;
      }

      if (!rowFound)
      {
        matrix[0].add(shape);
      }
    }
  }
  return matrix;
}
