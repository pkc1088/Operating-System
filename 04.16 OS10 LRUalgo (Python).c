class Node:
    def __init__(self, data, prev=None, next=None):
        self.data = data
        self.prev = prev
        self.next = next
    
class DoublyLinkedList:
    def __init__(self, cacheSize):
        self.cacheSize = cacheSize
        self.head = Node("")
        self.tail = Node("")
        self.head.next = self.tail
        self.tail.prev = self.head
    
    def LRU(self, data):
        print("[Put " + data + "]", end=" ")
        node = self.head.next
        while(node.data):
            if node.data == data:
                self.cacheHit(node, data)
                return
            node = node.next
        self.cacheMiss(data)
    
    # ���� �Ǿ����� �̵�
    def cacheHit(self, node, data):
        self.removeNode(node)
        self.addFront(data)
        print("[Hit ]", end=" ")
        self.printAll()
    
    # node ����
    def removeNode(self, node):
        node.prev.next, node.next.prev = node.next, node.prev
       
    # head �� �ٷ� �ڿ� ���� �ֱ�
    def addFront(self, data):
        newNode = Node(data)
        self.head.next.prev = newNode
        newNode.next = self.head.next
        self.head.next = newNode
        newNode.prev = self.head
        
    # ������ �Ǿտ� �߰� (cacheSize ���� Ŀ���� tail�� ����� ��� ����)
    def cacheMiss(self, data):
        self.addFront(data)
        if self.totalLen() > self.cacheSize:
            self.removeTail()
        print("[Miss]", end=" ")
        self.printAll()
        
    # linked list �� �� ���� ��ȯ
    def totalLen(self):
        answer = 0
        node = self.head.next
        while(node.data):
            answer += 1
            node = node.next
        return answer
        
    # tail �� ���� ����� ���� ����
    def removeTail(self):
        self.tail.prev.prev.next = self.tail
        self.tail.prev = self.tail.prev.prev
      
    # For Debug  
    # head ���� tail ���� ��ȯ�ϸ鼭 date ���� ���
    def printAll(self):
        node = self.head.next
        while(node.data):
            print(node.data, end="")
            node = node.next
            if (node.data):
                print(" -> ", end="")
        print()

test = DoublyLinkedList(3)
inputArray = ["1", "2", "1", "3", "4", "1", "5", "4"]
for input in inputArray:
    test.LRU(input)
    
    
    
//////// java
//��ó : https://jins-dev.tistory.com/entry/LRU-Cache-Algorithm-���� [Jins' Dev Inside]

