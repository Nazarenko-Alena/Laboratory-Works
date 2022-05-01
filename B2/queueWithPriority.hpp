#ifndef QUEUE_WITH_PRIORITY_HPP
#define QUEUE_WITH_PRIORITY_HPP

#include <list>
#include <stdexcept>

template<typename QueueElement>
class QueueWithPriority
{
public:
  enum ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  void putElement(const QueueElement& element, const ElementPriority priority);
  void deleteElement();
  QueueElement getElement();
  void accelerate();
  bool empty() const;
private:
  std::list<QueueElement> low_;
  std::list<QueueElement> normal_;
  std::list<QueueElement> high_;
};

template<typename QueueElement>
void QueueWithPriority<QueueElement>::putElement(const QueueElement& element, const ElementPriority priority)
{
  if (priority == ElementPriority::LOW)
  {
    low_.push_back(element);
  }
  else if (priority == ElementPriority::HIGH)
  {
    high_.push_back(element);
  }
  else if (priority == ElementPriority::NORMAL)
  {
    normal_.push_back(element);
  }
  else
  {
    throw std::invalid_argument("Incorrect priority");
  }
}

template<typename QueueElement>
void QueueWithPriority<QueueElement>::deleteElement()
{
  if (!empty())
  {
    if (!high_.empty())
    {
      high_.pop_front();
    }
    else if (!normal_.empty())
    {
      normal_.pop_front();
    }
    else
    {
      low_.pop_front();
    }
  }
  else
  {
    throw std::out_of_range("Queue is empty");
  }
}

template<typename QueueElement>
QueueElement QueueWithPriority<QueueElement>::getElement()
{
  if (!empty())
  {
    if (!high_.empty())
    {
      return high_.front();
    }
    else if (!normal_.empty())
    {
      return  normal_.front();
    }
    else
    {
      return low_.front();
    }
  }
  else
  {
    throw std::out_of_range("Queue is empty");
  }
}

template<typename QueueElement>
void QueueWithPriority<QueueElement>::accelerate()
{
  high_.splice(high_.end(), low_);
}

template<typename QueueElement>
bool QueueWithPriority<QueueElement>::empty() const
{
  return(high_.empty() && normal_.empty() && low_.empty());
}

#endif
