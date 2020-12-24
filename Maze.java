
public class Maze {
	
	private Block s = new Block('o');
	private Block f = new Block('*');
	private Block w = new Block('#');
	private Block p = new Block('x');
	private Block[][] maze;
	
	public Maze() {
		maze = new Block[6][6];
		for(int x = 0; x < 6; x++ ) {
			for (int y = 0; y < 6; y++) {
				if(x==0||x==5||y==0||y==5) maze[x][y] = w;
				else if(x==1&&y==1)maze[x][y] = s;
				else if(x==4&&y==1)maze[x][y] = f;
				else maze[x][y] = new Block('x');
			}
		}
	}
	
	public Maze(Block[][] a) {
		this.maze = a;
	}
	public Maze(int width, int height) {
		maze = new Block[width][height];
	}
	
	public Block get(int xPos, int yPos) {
		return maze[xPos][yPos];
	}
	public Block get(Loc l) {
		return maze[l.getX()][l.getY()];
	}
	public void set(int xPos, int yPos, Block val) {
		maze[xPos][yPos] = val;
	}
	public void setXY(int x, int y) {
		maze = new Block[x][y];
	}
	public int getWidth() {
		return maze.length;
	}
	public int getHeight() {
		return maze[0].length;
	}
	public Block[][] getMaze() {
		return this.maze;
	}
	public Loc getStart() {
		for(int x = 0; x < maze.length; x++) {
			for(int y = 0; y < maze[0].length; y++) {
				if(maze[x][y].equals(s))return new Loc(x,y);
			}
		}
		return null;
	}
	public Loc getFinish() {
		for(int x = 0; x < maze.length; x++) {
			for(int y = 0; y < maze[0].length; y++) {
				if(maze[x][y].equals(f))return new Loc(x,y);
			}
		}
		return null;
	}
	public String toString() {
		String result = "";
		for(Block[] blocs: maze) {
			result+= "[";
			for(Block b: blocs) {
				result+= b+",";
			}
			result = result.substring(0, result.length()-1);
			result+="]\n";
		}
		return result;
	}
}
