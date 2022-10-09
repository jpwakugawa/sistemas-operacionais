array = {}

n = 10
for i=1,n do
	array[i] = {}

	for j=1,n do
		random = math.random(n)
		if (i==1)
			then
			array[i][j] = random
		else
			prev = array[i-1][random]
			array[i][j] = prev
		end
	end
end

function printArray()
	for i=1,n do
		line = ""
		for j=1,n do
			line = line .. " " .. tostring(array[i][j])
		end
		print(line)
	end
end

printArray()
