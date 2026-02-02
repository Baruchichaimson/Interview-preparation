# Bank Backend (Node.js)

Backend system for a banking application.

## Features
- User registration with email verification
- JWT authentication
- Account management
- Money transfers between users
- Transactions history
- Password reset via email

## Tech Stack
- Node.js
- Express
- MongoDB + Mongoose
- JWT
- Nodemailer

## Installation

```bash
npm install

## Database setup

Set `MONGO_URI` in `bank-backend/.env`. If you don't set it, the backend defaults to
`mongodb://127.0.0.1:27017/bank-11`. Ensure MongoDB is running before starting the server.

Example (local MongoDB):

```bash
mongod --dbpath /path/to/db
```

Example (Docker):

```bash
docker run --name bank-mongo -p 27017:27017 -d mongo:6
```

## Troubleshooting local MongoDB

If you see `ECONNREFUSED 127.0.0.1:27017` (like in MongoDB Compass), MongoDB isn't running
or isn't listening on port 27017. Make sure the daemon is started before running the app.

If your local MongoDB is a standalone instance, **do not** include `replicaSet=rs0` in
`MONGO_URI`—that requires running a replica set.