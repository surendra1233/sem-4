# from simulator import copy
import copy,time

class Team29:

    def __init__(self):
        self.blocks = {}
        self.player = "x"
        self.opponent = "o"
        self.count = 0
        self.start = time.time()
    def find_valid_move_cells(self, old_move,small_boards_status,big_boards_status):
		#returns the valid cells allowed given the last move and the current board state
		allowed_cells = []
		allowed_small_board = [old_move[1]%3, old_move[2]%3]
		#checks if the move is a free move or not based on the rules

		if old_move == (-1,-1,-1) or (small_boards_status[0][allowed_small_board[0]][allowed_small_board[1]] != '-' and small_boards_status[1][allowed_small_board[0]][allowed_small_board[1]] != '-'):
			for k in range(2):
				for i in range(9):
					for j in range(9):
						if big_boards_status[k][i][j] == '-' and small_boards_status[k][i/3][j/3] == '-':
							allowed_cells.append((k,i,j))

		else:
			for k in range(2):
				if small_boards_status[k][allowed_small_board[0]][allowed_small_board[1]] == "-":
					for i in range(3*allowed_small_board[0], 3*allowed_small_board[0]+3):
						for j in range(3*allowed_small_board[1], 3*allowed_small_board[1]+3):
							if big_boards_status[k][i][j] == '-':
								allowed_cells.append((k,i,j))

		return allowed_cells
    
    def check_valid_move(self, old_move, new_move,small_boards_status,big_boards_status):
		#checks if a move is valid or not given the last move
		if (len(old_move) != 3) or (len(new_move) != 3):
			return False
		for i in range(3):
			if (type(old_move[i]) is not int) or (type(new_move[i]) is not int):
				return False
		if (old_move != (-1,-1,-1)) and (old_move[0] < 0 or old_move[0] > 1 or old_move[1] < 0 or old_move[1] > 8 or old_move[2] < 0 or old_move[2] > 8):
			return False
		cells = self.find_valid_move_cells(old_move,small_boards_status,big_boards_status)
		return new_move in cells
    
    
    def update(self, old_move, new_move, ply,small_boards_status,big_boards_status):
		#updating the game board and small_board status as per the move that has been passed in the arguements
		if(self.check_valid_move(old_move, new_move,small_boards_status,big_boards_status)) == False:
			return 'UNSUCCESSFUL', False
		big_boards_status[new_move[0]][new_move[1]][new_move[2]] = ply

		x = new_move[1]/3
		y = new_move[2]/3
		k = new_move[0]

		#checking if a small_board has been won or drawn or not after the current move
		bs = big_boards_status[k]
		for i in range(3):
			#checking for horizontal pattern(i'th row)
			if (bs[3*x+i][3*y] == bs[3*x+i][3*y+1] == bs[3*x+i][3*y+2]) and (bs[3*x+i][3*y] == ply):
				small_boards_status[k][x][y] = ply
				return 'SUCCESSFUL', True
			#checking for vertical pattern(i'th column)
			if (bs[3*x][3*y+i] == bs[3*x+1][3*y+i] == bs[3*x+2][3*y+i]) and (bs[3*x][3*y+i] == ply):
				small_boards_status[k][x][y] = ply
				return 'SUCCESSFUL', True
		#checking for diagonal patterns
		#diagonal 1
		if (bs[3*x][3*y] == bs[3*x+1][3*y+1] == bs[3*x+2][3*y+2]) and (bs[3*x][3*y] == ply):
			small_boards_status[k][x][y] = ply
			return 'SUCCESSFUL', True
		#diagonal 2
		if (bs[3*x][3*y+2] == bs[3*x+1][3*y+1] == bs[3*x+2][3*y]) and (bs[3*x][3*y+2] == ply):
			small_boards_status[k][x][y] = ply
			return 'SUCCESSFUL', True
		#checking if a small_board has any more cells left or has it been drawn
		for i in range(3):
			for j in range(3):
				if bs[3*x+i][3*y+j] =='-':
					return 'SUCCESSFUL', False
		small_boards_status[k][x][y] = 'd'
		return 'SUCCESSFUL', False
    
    
    def block_status(self,block):

        for i in range(3):
            if block[i][0]==block[i][1]==block[i][2] and block[i][1] != "-":
                return block[i][0]
            if block[0][i] == block[1][i] == block[2][i] and block[1][i] != "-":
                return block[0][i]
        
        if block[0][0]==block[1][1]==block[2][2] and block[0][0] !="-":
            return block[0][0]

        if block[0][2]==block[1][1]==block[2][0] and block[1][1] !="-":
            return block[1][1]

        for i in range(3):
            for j in range(3):
                if block[i][j]=='-':
                    return "-"
        
        return "d"

    def find_terminal_state(self,small_boards_status):
		#checks if the game is over(won or drawn) and returns the player who have won the game or the player who has higher small_boards in case of a draw

		cntx = 0
		cnto = 0
		cntd = 0
	
		for k in range(2):
			bs = small_boards_status[k]
			for i in range(3):
				for j in range(3):
					if bs[i][j] == 'x':
						cntx += 1
					if bs[i][j] == 'o':
						cnto += 1
					if bs[i][j] == 'd':
						cntd += 1
			for i in range(3):
				row = bs[i]
				col = [x[i] for x in bs]
				#print row,col
				#checking if i'th row or i'th column has been won or not
				if (row[0] =='x' or row[0] == 'o') and (row.count(row[0]) == 3):	
					return (row[0],'WON')
				if (col[0] =='x' or col[0] == 'o') and (col.count(col[0]) == 3):
					return (col[0],'WON')
			#check diagonals
			if(bs[0][0] == bs[1][1] == bs[2][2]) and (bs[0][0] == 'x' or bs[0][0] == 'o'):
				return (bs[0][0],'WON')
			if(bs[0][2] == bs[1][1] == bs[2][0]) and (bs[0][2] == 'x' or bs[0][2] == 'o'):
				return (bs[0][2],'WON')

		if cntx+cnto+cntd < 18:		#if all small_boards have not yet been won, continue
			return ('CONTINUE', '-')
		elif cntx+cnto+cntd == 18:							#if game is drawn
			return ('NONE', 'DRAW')


    def checkAllowedMoves(self,block):
        allowed=[]
        for i in range(3):
            for j in range(3):
                if block[i][j] == "-":
                    allowed.append((i, j))
        return allowed

    def block_score(self,block):
        block = tuple([tuple(block[i]) for i in range(3)])
        moves = []
        if block not in self.blocks:
            stat = self.block_status(block)

            if stat == self.player:
                self.blocks[block] = 1
            elif stat == self.opponent:
                self.blocks[block] = 0
            elif stat == "d":
                self.blocks[block] = 0.2
            else:
                moves = self.checkAllowedMoves(block)
                #we play the next move
                our_scores = []
                playBlock = [list(block[i]) for i in range(3)]
                for move in moves:
                        playBlock[move[0]][move[1]] = self.player
                        our_scores.append(self.block_score(playBlock))
                        playBlock[move[0]][move[1]] = "-"
                #opponent plays the next move
                op_scores = []
                for move in moves:
                        playBlock[move[0]][move[1]] = self.opponent
                        op_scores.append(self.block_score(playBlock))
                        playBlock[move[0]][move[1]] = "-"
                self.blocks[block] = 0.5*(max(our_scores)+min(op_scores))
            
        return self.blocks[block]

    def board_score(self,small_boards_status,big_boards_status,flag):
        scores = [[],[]]
        op_scores = [[],[]]
        cntx = 0
        cnto = 0
        cntd = 0
        for k in range(2):
			bs = small_boards_status[k]
			for i in range(3):
				for j in range(3):
					if bs[i][j] == 'x':
						cntx += 1
					if bs[i][j] == 'o':
						cnto += 1
					if bs[i][j] == 'd':
						cntd += 1
        
        if cntx+cnto+cntd == 18:							#if game is drawn
			return 50
        for k in range(2):
            for i in range(3):
                for j in range(3):
                    temp = [[big_boards_status[k][i*3+r][j*3+c] for r in range(3)]for c in range(3)]
                    
                    #score for each block
                    scores[k].append(self.block_score(temp))

        
        for k in range(2):
            for i in range(3):
                for j in range(3):
                    temp = [[0 for r in range(3)]for c in range(3)]
                    for r in range(3):
                        for c in range(3):
                            if big_boards_status[k][i*3+r][j*3+c]==self.player:
                                temp[r][c] = self.opponent
                            elif big_boards_status[k][i*3+r][j*3+c]==self.opponent:
                                temp[r][c] = self.player
                            else:
                                temp[r][c] = "-"
                    
                    op_scores[k].append(self.block_score(temp))

        
        #get line scores
        lines = [[],[]]
        op_lines = [[],[]]

        for k in range(2):
            for i in range(3):
                    lines[k].append(scores[k][3*i]*scores[k][3*i+1]*scores[k][3*i+2])
                    op_lines[k].append(op_scores[k][3*i]*op_scores[k][3*i+1]*op_scores[k][3*i+2])
                    
                    lines[k].append(scores[k][i]*scores[k][i+3]*scores[k][i+6])
                    op_lines[k].append(op_scores[k][i]*op_scores[k][i+3]*op_scores[k][i+6])
            
            lines[k].append(scores[k][0]*scores[k][4]*scores[k][8])
            op_lines[k].append(op_scores[k][0]*op_scores[k][4]*op_scores[k][8])

            lines[k].append(scores[k][2]*scores[k][4]*scores[k][6])
            op_lines[k].append(op_scores[k][2]*op_scores[k][4]*op_scores[k][6])


        #return sum of the scores of lines
        if 1 in lines[0]:
            return 100
        elif 1 in lines[1]:
            return 100
        elif 1 in op_lines[0]:
            return -100
        elif 1 in op_lines[1]:
            return -100
        else:
            # if flag==self.player:
            return max(sum(lines[0])-sum(op_lines[0]),sum(lines[1])-sum(op_lines[1]))
            # else:
            #     return min(sum(lines[0])-sum(op_lines[0]),sum(lines[1])-sum(op_lines[1]))
    def move(self, board, old_move, flag):
        self.start = time.time()
        if self.count==0 and flag != self.player:
            self.opponent = "x"
            self.player = "o"
            depth = 4
        elif self.count==0:
            depth = 4
        elif self.count<=30:
            depth = 4
        elif self.count<=60:
            depth = 4
        elif self.count<=70:
            depth = 4
        else:
            depth = 5
        # else:
        #     depth = 4 

        if self.count==0 and flag=="x":
            self.count+=1
            t = [["-","-","-"],["-","-","-"],["-","-","-"]]
            a = self.block_score(t)
            return (0,4,4)

        big_boards_status = copy.deepcopy(board.big_boards_status)
        small_boards_status = copy.deepcopy(board.small_boards_status)

        if big_boards_status[old_move[0]][old_move[1]][old_move[2]] == self.player:
            score,next_move= self.alphabetapruning(small_boards_status,big_boards_status,depth,old_move, -100000000, 100000000,flag,True)
        else:    
            score,next_move= self.alphabetapruning(small_boards_status,big_boards_status,depth,old_move, -100000000, 100000000,flag,False)            
        self.count+=1
        # print next_move,score, flag, depth
        return next_move


    def alphabetapruning(self,small_boards_status,big_boards_status,depth,old_move,alpha,beta,flag,bonus):
        stat = self.find_terminal_state(small_boards_status)

        if stat[0] == self.player:
            return 100,()
        elif stat[0] == self.opponent:
            return -100,()
        elif stat[1] == "DRAW":
            return 50,()

        max_player = False
        if flag==self.player:
            max_player = True
        
        # temp = BigBoard()
        temp_big_boards_status = copy.deepcopy(big_boards_status)
        temp_small_boards_status = copy.deepcopy(small_boards_status)   

        moves = self.find_valid_move_cells(old_move,small_boards_status,big_boards_status)
        # random.shuffle(moves)
        move_scores = []
        
        siz = len(moves)

        if siz > 18 and self.count<=60:
            depth -= 1

        i = 0
        if depth > 0 and time.time()-self.start<=22:
            for m in moves:
                self.update(old_move,m,flag,temp_small_boards_status,temp_big_boards_status)
                move_scores.append((self.board_score(temp_small_boards_status,temp_big_boards_status,flag),i))
                temp_big_boards_status[m[0]][m[1]][m[2]] = "-"
                temp_small_boards_status[m[0]][m[1]/3][m[2]/3] = "-"
                i+=1
        
        #sort them in decreasing order

            sorted(move_scores,key=lambda x: x[0], reverse=max_player)

        bestmove = ()


        # print moves



        if depth>1 and time.time()-self.start<=22:
            for i in range(siz):
                self.update(old_move,moves[move_scores[i][1]],flag,temp_small_boards_status,temp_big_boards_status)
                if max_player:
                    if temp_small_boards_status[moves[move_scores[i][1]][0]][moves[move_scores[i][1]][1]/3][moves[move_scores[i][1]][2]/3] == self.player and bonus == False:
                        s,m =  self.alphabetapruning(temp_small_boards_status,temp_big_boards_status,depth-1,moves[move_scores[i][1]],alpha,beta,self.player,True)
                        # if s < beta:
                        #     beta = s
                        #     bestmove = moves[move_scores[i][1]]
                    
                        # if alpha >= beta:
                        #     break
                    else:
                        s,m = self.alphabetapruning(temp_small_boards_status,temp_big_boards_status,depth-1,moves[move_scores[i][1]],alpha,beta,self.opponent,False)
                    if s > alpha:
                        alpha = s
                        bestmove = moves[move_scores[i][1]]
                    
                    if alpha >= beta:
                        break
                    if time.time()-self.start>22:
                        return move_scores[0][0],moves[move_scores[0][1]]                        
                             
                else:
                    if temp_small_boards_status[moves[move_scores[i][1]][0]][moves[move_scores[i][1]][1]/3][moves[move_scores[i][1]][2]/3] == self.opponent and bonus == False:
                        s,m = self.alphabetapruning(temp_small_boards_status,temp_big_boards_status,depth-1,moves[move_scores[i][1]],alpha,beta,self.opponent,True)
                        # if s > alpha:
                        #     alpha = s
                        #     bestmove = moves[move_scores[i][1]]

                        # if alpha >= beta:
                        #     break
                    else:
                        s,m =  self.alphabetapruning(temp_small_boards_status,temp_big_boards_status,depth-1,moves[move_scores[i][1]],alpha,beta,self.player,False)
                    if s < beta:
                        beta = s
                        bestmove = moves[move_scores[i][1]]

                    if alpha >= beta:
                        break
                    
                    if time.time()-self.start>22:
                        return move_scores[0][0],moves[move_scores[0][1]]
                
                temp_small_boards_status[moves[move_scores[i][1]][0]][moves[move_scores[i][1]][1]/3][moves[move_scores[i][1]][2]/3] = "-"
                temp_big_boards_status[moves[move_scores[i][1]][0]][moves[move_scores[i][1]][1]][moves[move_scores[i][1]][2]] = "-"
        elif depth > 0 and time.time()-self.start<=22:
            return move_scores[0][0],moves[move_scores[0][1]]
        else:
            return self.board_score(small_boards_status,big_boards_status,flag),bestmove
        # if depth==5:
            # print move_scores

        if max_player:
            return alpha,bestmove
        else:
            return beta,bestmove