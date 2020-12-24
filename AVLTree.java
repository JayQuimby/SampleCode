package newPackage;

public class AVLTree<T extends Comparable<T>, V> extends Tree<T, V>{
	
	
	public AVLTree() {
		super();
	}
	
	public AVLTree(T data, V value) {
		super(data, value);
		this.getRoot().calcDiff();
	}
	
	public AVLTree(TreeNode<T, V> root) {
		super(root);
		this.getRoot().calcDiff();
	}
	
	public TreeNode<T, V> insert(T data, V value,TreeNode<T, V> pre){
		
		if(pre == null || pre.getData() == null) {
			pre = new TreeNode<T, V>(data, value);
			grow();
		}
		
		else if(data.compareTo(pre.getData()) < 0) {
			
			pre.setCL(insert(data, value, pre.getCL()));
			
			if(pre.getDiff() <= -2)
				
				if(data.compareTo(pre.getCL().getData()) < 0)
					pre = this.RWL(pre);
				else 
					pre = this.DWL(pre);
		}
		
		else if(data.compareTo(pre.getData()) > 0) {
			
			pre.setCR(insert(data, value,pre.getCR()));

			if(pre.getDiff() >= 2) 
				
				if(data.compareTo(pre.getCR().getData()) > 0) 
					pre = this.RWR(pre);
				else
					pre = this.DWR(pre);
		}
		
		else ;
		
		return pre;
	}
	
	public TreeNode <T, V> delete(TreeNode<T, V> n, T key){
		if (n == null) return n;
		
		if (key.compareTo(n.getData()) < 0)
			n.setCL(delete(n.getCL(), key));
		
		else if (key.compareTo(n.getData())>0)
			n.setCR(delete(n.getCR(), key));
		
		else {
			
			if(n.getCL() == null || n.getCR() == null) {
				
				TreeNode<T, V> temp = (n.getCL()== null)? n.getCR() : n.getCL();
				if(temp == null) {
					temp = n;
					n = null;
				}
				else {
					n = temp;
				}
			}
			else {
				TreeNode<T, V> temp = minValue(n.getCR());
				n.setData(temp.getData());
				n.setCR(delete(n.getCR(), temp.getData()));
			}
			
		}
		if(n == null) return n;
		
		if(n.getDiff() > 1) {
			if(n.getCR().getDiff() > 0) {
				return this.RWR(n);
			}
			else {
				return this.DWR(n);
			}
		}
		else if (n.getDiff() < -1){
			if(n.getCL().getDiff() < 0) {
				return this.RWL(n);
			}
			else {
				return this.DWL(n);
			}
		}
		
		return n; 
	}
	
	public TreeNode<T, V> RWL(TreeNode<T, V> r){
		TreeNode<T, V> n = r.getCL();
		r.setCL(n.getCR());
		n.setCR(r);
		return n;
	}
	
	public TreeNode<T, V> RWR(TreeNode<T, V> r){
		TreeNode<T, V> n = r.getCR();
		r.setCR(n.getCL());
		n.setCL(r);
		return n;
	}
	
	public TreeNode<T, V> DWL(TreeNode<T, V> r){
		r.setCL(RWR(r.getCL()));
		return RWL(r);
	}
	
	public TreeNode<T, V> DWR(TreeNode<T, V> r){
		r.setCR(RWL(r.getCR()));
		return RWR(r);
	}
	
	public void assignDiffs() {
		TreeNode<T, V> node = this.getRoot();
		this.ADiffHelp(node);
	}
	
	public void ADiffHelp(TreeNode<T, V> node) {
		node.calcDiff();
		if(node.hasLC())  node.getCL().calcDiff();
		if(node.hasRC())  node.getCR().calcDiff();
	}
	
	public void delete(T data) {
		if(this.contains(data, null)) {
			delete(this.getRoot(), data);
			demo();
		}
	}
	
	public void delete(T data, V value) {
		if(this.contains(data, value)) {
			delete(this.getRoot(), data);
			demo();
		}
	}
	
	/*public TreeNode<T, V> deleteNode(T data, TreeNode<T, V> p) {
		
		if(p == null) {
			return p;
		}
	}*/
}