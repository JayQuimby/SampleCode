public class LinkList {
	
	private Link head;
	private Link tail;
	public int size = 0;
	
	public LinkList(Link head){
		this.head = head;
		this.tail = head;
		size++;
	}
	
	public LinkList(){
		head = null;
		tail = null;
	}
	
	
	public void add(String str){
		if(this.head == null) addFirst(str);
		else{
			Link temp = head;
			while(temp.getNext()!= null)temp = temp.getNext();
			temp.setNext(new Link(str,null,temp));
			this.tail = temp.getNext();
		}
		size++;
	}
	
	public void addLink(Link L){
		if(this.head == null) addFirst(L);
		else{
			Link temp = head;
			while(temp.getNext()!= null)temp = temp.getNext();
			temp.setNext(L) ;
			L.setPrev(temp);
			this.tail = L;
		}
		size++;
	}
	
	public void addFirst(String str){
		head = new Link(str, head, null);
		size++;
	}
	
	public void addFirst(Link L){
		L.setNext(this.head);
		this.head.setPrev(L);
		this.head = L;
		size++;
	}
	
	public void addAfter(String key, String dataPack){
		Link temp = this.head;
		while(temp.getNext()!= null&&!temp.getData().equals(key)) temp = temp.getNext();
		
		if (temp.getNext()!=null) temp.setNext(new Link(dataPack, temp.getNext(),temp)) ;
		
		else temp.setNext(new Link(dataPack, null, temp));
		
		size++;
	}
	
	public void addAfter(String key, Link dataPack){
		Link temp = head;
		while(temp.getNext()!= null&&!temp.getData().equals(key)) temp = temp.getNext();
		
		if (temp!=null){ dataPack.setNext(temp.getNext()); temp.setNext(dataPack); dataPack.setPrev(temp);size++;}
		return;
		
	}
	
	public void addBefore(String key, String dataPack){	
		Link temp = head;
		Link last = head;
		
		if(head==null) { System.out.println("key not found :"+ key);return;}
		
		if(head.getData().equals(key)) addFirst(dataPack);
		
		while(temp!=null&&!temp.getData().equals(key)){
			last = temp;
			temp.setNext(temp.getNext());
		}
		if(temp!= null) last.setNext(new Link(dataPack, temp, last));
		size++;
	}
	
	public void addBefore(String key, Link dataPack){	
		Link temp = head;
		if(head==null) return;	
		if(head.getData().equals(key))addFirst(dataPack);
		
		while(temp!=null&&!temp.getData().equals(key)){
			temp = temp.getNext();
		}
		if (temp!=null){ dataPack.setNext(temp.getNext()); temp.setNext(dataPack) ; }
		size++;
	}
	
	public void addSortedLink(String data) {
		if(this.getHead()==null) {
			addFirst(data);
		}
		else if(this.getHead().getData().compareTo(data)>0) {
			addFirst(data); 
			}
		else if(this.getHead().getData().equals(data)) {
			this.getHead().increment();
		}
		else {
			Link cur = this.getHead();
			Link next = cur.getNext();
			while(next != null) {
				if(next.getData().compareTo(data)==0) {next.increment();return;}
				else if(next.getData().compareTo(data)>0) {cur.setNext(new Link(data, next, cur));return;}
				cur = next;
				next = cur.getNext();
			}
			cur.setNext(new Link(data, null, cur));
		}
	}
	
	public void remove(String str){
		Link temp = head;
		Link last = null;
		
		if (head == null)return;
		if (head.getData().equals(str)){
			head = head.getNext();
			return;
		}	
		
		while(temp!=null&&!temp.getData().equals(str)){
			last = temp;
			temp = temp.getNext();
		}
		last.setNext(temp.getNext());
		last.getNext().setPrev(last);
	}
	
	public void removeLink(Link L){
		Link temp = head;
		Link last = null;
		
		if (head == null)return;
		if (head.getData().equals(L.getData())){
			head = head.getNext();
			return;
		}	
		
		while(temp!=null&&!temp.getData().equals(L.getData())){
			last = temp;
			temp = temp.getNext();
		}
		if(temp == null)return;
		last.setNext(temp.getNext());
		last.getNext().setPrev(last);
	}
	
	public String toString(){
        String retStr ="Contents:\n";

        Link current = head;
        while(current != null){
            retStr += current.toString() + ", ";
            current = current.getNext();
        }
		retStr+="\n";
        return retStr;
    }
	
	public LinkList reverse(){
		
		LinkList result = new LinkList(this.getLast());
		LinkList oldList = this;
		
		while(oldList != null){
			Link temp = this.getHead();
			while(temp.getNext()!= null){
				temp = temp.getNext();
			}
			result.addLink(temp);
		}
		return result;
	}

	public void copy(LinkList copyLinks){
		Link cLink = copyLinks.getHead();
		this.head = cLink;
	}
	public Link getHead(){
		return this.head;
	}
	
	public void clear() {
		head = null;
	}
	
	public String getCount(String data) {
		Link temp = this.head;
		while (temp.getNext()!= null) {
			if(temp.getData().equals(data))return temp.toString();
			temp = temp.getNext();
			}
		return null;
	}
	
	public boolean contains(WordNode w) {
		Link temp = this.getHead();
		while(temp.getNext()!=null) {
			if(w.equals(temp.getNode()))return true;
		}
		return false;
	}
	
	public void removeHead() {
		head = head.getNext();
	}
	
	public Link getLast() {
		return tail;
	}
}
