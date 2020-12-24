import java.util.Comparator;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;

public class QuickSorter <T>{
	
	ArrayList<T> arr;
	Comparator<T> comp;
	
	public QuickSorter(Collection<T> arr, Comparator<T> comp)
	{
		this.arr = new ArrayList<T>(arr);
		
		this.comp = comp;
	}
	
	void sortI(ArrayList<T> arr) 
    { 
        int n = arr.size(); 
        
        for (int i = 1; i < n; ++i) { 
        	
            T key = arr.get(i); 
            
            int j = i - 1; 
  
            while (j >= 0 && comp.compare(arr.get(j), key) > 0) { 
                arr.set(j+1, arr.get(j)); 
                j--; 
            } 
            arr.set(j+1, key); 
        } 
    } 
	
	public void sortQ(ArrayList<T> arr, int low, int high, Comparator<T> comp) 
    { 
        if(arr.size()< 20) {
        	
        	sortI(arr);
        	
        	return;
        }
        
        if (high <= low) return;
        
        int lt = low, gt = high;
        
        T v = arr.get(low);
        
        int i = low + 1;
        
        while (i <= gt) {
        	
            int cmp = comp.compare(arr.get(i),v);

            if(cmp < 0) exch(arr, lt++, i++);
            
            else if (cmp > 0) exch(arr, i, gt--);
            
            else i++;
        }

        sortQ(arr, low, lt-1, comp);
        sortQ(arr, gt+1, high, comp);
    } 
	
	public void sortQ(ArrayList<T> arr) 
    {	
		Comparator<T> comp = this.comp;
		
		int low = 0;
		
		int high = arr.size()-1;
        
		this.sortQ(arr,low,high,comp);
    } 
	
	private void exch(ArrayList<T> a, int i, int j) 
	{
        T swap = a.get(i);
        
        a.set(i, a.get(j));
        
        a.set(j, swap);
    }
}
