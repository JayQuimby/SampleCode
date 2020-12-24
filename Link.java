
public class Link implements Comparable<Link>{

	private Link next;
	private Link prev;
	private WordNode word;
	
	public Link(String data, Link next){
		this.next = next; 
		this.word = new WordNode(data);
		this.prev = null;
	}
	
	public Link(String data, Link next, Link prev) {
		this.next = next;
		this.prev = prev;
		this.word = new WordNode(data);
	}
	
	public Link(String data){
		this.next = null;
		this.prev = null;
		this.word = new WordNode(data);
	}
	
	public Link(Link next){
		this.word = new WordNode("");
		this.next = next; 
	}
	
	public Link(Link next, Link prev) {
		this.next = next;
		this.prev = prev;
		this.word = new WordNode("");
	}
	
	public Link(){
		this.word = new WordNode("");
		this.next= null;
	}
	
	public String getData(){
		return this.word.getWord();
	}
	
	public Link getNext(){
		return this.next;
	}
	
	public Link getPrev() {
		return this.prev;
	}
	
	public void setNext(Link L){
		next = L;
	}
	
	public void setPrev(Link prev) {
		this.prev = prev;
	}
	public String toString(){
		return this.word.toString();
	}
	public boolean isNull() {
		if(this.word.getWord()==null||this == null)return true;
		return false;
	}
	
	public void increment() {
		word.increment();
	}
	
	public WordNode getNode() {
		return word;
	}

	@Override
	public int compareTo(Link link){
		if(this.isNull()||link.isNull())return -1;
		return this.toString().toLowerCase().compareTo(link.toString().toLowerCase());
		
	}

}