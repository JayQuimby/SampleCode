package newPackage;

public class TreeMap<T extends Comparable<T>,V> extends java.util.ArrayList<AVLTree<T,V>>{
	
	private static final long serialVersionUID = 1L;
	private static final int DEFAULT_SIZE = 500;
	
	private int elements = 0;
	
	public TreeMap() {
		super();
		for(int x = 0; x < DEFAULT_SIZE; x++) {
			this.add(new AVLTree<T, V>(null, null));
		}
		
	}
	
	public TreeMap(int items) {
		super();
		int Msize = (int) (2.75*items);
		for(int x = 0; x < Msize; x++) {
			this.add(new AVLTree<T, V>(null, null));
		}
	}
	
	public void add(T key, V val) {
		int hash = hashIndex(key);
		hash = Math.abs(hash);
		if(!this.get(hash).contains(key, val)) {
			this.get(hash).insert(key, val);
			elements++;
		}
	}
	
	public void delete(T key, V val) {
		int hash = hashIndex(key);
		if(this.get(hash).contains(key, val)) {
			this.get(hash).delete(key, val);
		}
	}
	
	public int hashIndex(T key) {
		return (int) ((long) Math.abs(key.hashCode()) % this.size());
	}
	
	public int makeHash(T key) {
		int code = key.hashCode();
		code = (int) (code ^ (code >>> 32));
		code += code * (key.hashCode() % 32);
		return code;
	} 
	
	public boolean contains(T key, V val) {
		return (this.get(hashIndex(key)).contains(key, val)); 
	}
	
	public void printMap() {
		for(AVLTree<T, V> t : this) {
			t.printTree();
		}
	}
	
	public void printMapStats() {
		double col = 0;
		double unused = 0;
		int largestTree = 0;
		int largestHeight = 0;
		AVLTree<T,V> largest = this.get(0);
		for(int x = 0; x < this.size(); x++) {
			
			AVLTree<T, V> temp = this.get(x);
			
			if(!temp.isEmpty()) {
				
			col += (temp.numLeaves() > 1)? temp.numLeaves(): 0;	
//			System.out.print(temp.numLeaves());
			largestTree = (largestTree < temp.numLeaves())? temp.numLeaves(): largestTree;
			
			largest = (largest.numLeaves() < temp.numLeaves())? temp : largest ;
			
//			System.out.print(temp.height());
			largestHeight = (largestHeight < temp.height())? temp.height(): largestHeight;
			
			}
			else {
				unused++;
			}
		}
		System.out.println("There were "+ (int)col+" collisions: "+String.format("%.2f",((col/elements)*100))+"%\n"
				+ "The largest tree size was "+largestTree+" elements\n"
				+ "The largest tree height was "+largestHeight+" layers\n"
				+ "There were "+(int)unused+" un-used spaces: "+String.format("%.2f",((unused/this.size())*100))+"%\n"
				+ "The map size was: "+this.size()+"\n"
				+ "This is the largest collision tree:");
		largest.printTree();
	}
}
