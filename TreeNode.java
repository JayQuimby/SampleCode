package newPackage;

public class TreeNode<T extends Comparable<T>, V> implements Comparable<TreeNode<T, V>>{
	
	private T data = null;
	private V value = null;
	private int count = 0;
	private int AVLDiff;
	private TreeNode<T, V> childL = null;
	private TreeNode<T, V> childR = null;
	
	public TreeNode() {
		data = null;
	}
	
	public TreeNode(T data) {
		this.data = data;
	}
	
	public TreeNode(T data, V value) {
		this.data = data;
		this.value = value;
	}
	
	public TreeNode(T data, T left, T right) {
		this.data = data;
		childL = new TreeNode<T, V>(left);
		childR = new TreeNode<T, V>(right);
	}
	
	public T getData() {
		return this.data;
	}
	
	public V getValue() {
		return this.value;
	}
	
	public void setData(T data) {
		this.data = data;
	}
	
	public void setValue(V value) {
		this.value = value;
	}
	public void setCL(TreeNode<T, V> node) {
		childL = node;
	}
	
	public void setCR(TreeNode<T, V> node) {
		childR = node;
	}
	
	public void setCLT(Tree<T, V> left) {
		childL = left.getRoot();
	}
	
	public void setCRT(Tree<T, V> right) {
		childR = right.getRoot();
	}
	
	public TreeNode<T, V> getCL() {
		return childL;
	}
	
	public TreeNode<T, V> getCR() {
		return childR;
	}
	
	public void increment() {
		count++;
	}
	public int getCount() {
		return count;
	}
	
	public int compareTo(TreeNode<T, V> comp) {
		return this.getData().compareTo(comp.getData());
	}
	
	public boolean equals(TreeNode<T, V> comp) {
		if(comp.getData() != null) {
			return this.getData().equals(comp.getData()) && this.getData().equals(comp.getData());
		}
		else return false;
	}
	
	public boolean hasLC() {
		return (this.childL == null)? false : true;
	}
	
	public boolean hasRC() {
		return (this.childR == null)? false: true;
	}
	
	public String toString() {
		String result = (String) this.getValue().toString();
		return (this.getValue() == null)? this.getData().toString() : result;
	}
	
	public void calcDiff() {
		AVLDiff = diffHelp(this);
	}
	
	public int diffHelp(TreeNode<T, V> node) {
		if(node.hasLC() && node.hasRC()) {
			return (getHeight(node.getCR())-getHeight(node.getCL()));
		}
		
		else if(node.hasLC()) {
			return -getHeight(node.getCL());
		}
		
		else if(node.hasRC()) {
			return getHeight(node.getCR());
		}
		
		else {
			return 0;
		}
	}

	
	public int getDiff() {
		this.calcDiff();
		return this.AVLDiff;
	}
	
	public int getHeight(TreeNode <T, V> n) {
		if(!n.hasLC()&&!n.hasRC())return 1;
			
			int RH = (n.hasRC()) ? this.getHeight(n.getCR()) : 0;
			
			int LH = (n.hasLC()) ? this.getHeight(n.getCL()) : 0;
			
			//System.out.println(LH+", "+RH);
			
			return (1 + Math.max(LH, RH));
	}
	
}



