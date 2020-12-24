
/*
	- track path positions with a stack of Locations
	- at the current position
		- look in all 4 directions
		- if none of them are valid moves pop the stack
		- if it is a valid position then mark it as seen and push it onto the stack
		- if it is the end then return true and display the stack
*/
public class mazeSolver {
	private Stack2 agenda = new Stack2();
	private Maze m;
	private Loc start, cur, fin;
	
	public mazeSolver(Maze a) {
		m = a;
		start = a.getStart();
		cur = a.getStart();
		fin = a.getFinish();
		agenda.add(cur);
		m.get(cur).visit();
	}
	
	public void solve() {
		cur.setX(start.getX());
		cur.setY(start.getY());
		while(!agenda.isEmpty()) {
			Loc a = nextMove();
			if(a == null) { 
				agenda.remove();
				if(!agenda.isEmpty())cur = agenda.peek();
				System.out.println("Pop");
				System.out.println(agenda.getSize());
			}
			
			else if(a.equals(fin)) {
				System.out.println("Done");
				agenda.add(a);
				System.out.println("Number of moves: "+agenda.getSize());
				System.out.println("Move sequence: "+agenda);
				System.out.println(m);
				return;
			}
			
			else {
				agenda.add(a);
				System.out.println("Push");
				cur = a;
				System.out.println(agenda.getSize());
			}
			//System.out.println(m.get(2, 3));
		}
		System.out.println("The maze cannot be solved");
	}
	public Loc nextMove() {
		Block b;
		for(int num = 0; num < 4; num++) {
			switch (num) {
			case 0:
				b = m.get(cur.getX(), cur.getY()+1);
				if(!b.isWall() && !b.wasSeen()) {
					b.visit();
//					System.out.println(m.get(cur.getX(), cur.getY()+1));
					return new Loc(cur.getX(), cur.getY()+1);
				}
			case 1:
				b = m.get(cur.getX()+1, cur.getY());
				if(!b.isWall() && !b.wasSeen()) {
					b.visit();
//					System.out.println(m.get(cur.getX()+1, cur.getY()));
					return new Loc(cur.getX()+1, cur.getY());
				}
			case 2:
				b = m.get(cur.getX(), cur.getY()-1);
				if(!b.isWall() && !b.wasSeen()) {
					b.visit();
//					System.out.println(m.get(cur.getX(), cur.getY()-1));
					return new Loc(cur.getX(), cur.getY()-1);
				}
			case 3:
				b = m.get(cur.getX()-1, cur.getY());
				if(!b.isWall() && !b.wasSeen()) {
					b.visit();
//					System.out.println(m.get(cur.getX()-1, cur.getY()));
					return new Loc(cur.getX()-1, cur.getY());
				}
			default: return null;
			}
		}
		return null;
	}
	
}
