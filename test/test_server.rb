require 'sinatra'

set :port, 9494

get '/*' do
  filename = "test/fixtures/#{params['splat'].first}"
  File.read(filename)
end