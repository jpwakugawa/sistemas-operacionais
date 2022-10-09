nClock = os.clock()
array = {}

n = io.read("*n")

for i=1,n do
	array[i] = {}

	for j=1,n do
		co = coroutine.create(function (i, j)
		random = math.random(n)

		if (i==1)
			then
				array[i][j] = random
			else
				prev = array[i-1][random]
				array[i][j] = prev
			end
		end)

		coroutine.resume(co, i, j)
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

if (n <= 10) then printArray() end
print("Execution Time:", os.clock()-nClock)
