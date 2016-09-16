`make`

require './flatten'

RSpec.describe 'Flatten#collapse' do
	it 'lives on Array' do
		expect([1].respond_to?(:collapse)).to eq(true)
	end
	it 'applies a block to every element' do
		expect([1, 2].collapse { |e| e * 2 }).to eq([2, 4])
	end
	it 'flattens a nested array' do
		expect([1, [2]].collapse).to eq([1, 2])
	end
	it 'flattens and maps' do
		expect([1, [2, [3]]].collapse { |e| e * 2 }).to eq([2, 4, 6])
	end
end
