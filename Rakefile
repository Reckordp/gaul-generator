EXECUTABLE = "build/gaul.exe"
INCLUDE_PATH = "include"
FORMAT_SENYAP = "gcc -c src/%s.c -I%s -o build/%s.o"

script = Dir.glob("src/*.c")
obj_file = []

def gcc_senyap(nama_file)
	sh(FORMAT_SENYAP % [nama_file, INCLUDE_PATH, nama_file])
end

script.each do |s|
	sumber = File.basename(s.pathmap("src/%n"))
	nama_file = "build/%s.o" % sumber
	file nama_file do |t|
		gcc_senyap(sumber)
	end
	obj_file.push(nama_file)
end

file EXECUTABLE => obj_file do |t|
	sh("gcc %s -o %s" % [obj_file.join(" "), EXECUTABLE])
end

task default: [EXECUTABLE, :clean]
task :clean do
	obj_file.each do |objf|
		rm_rf objf
	end
end